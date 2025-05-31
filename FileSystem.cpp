#include "FileSystem.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>




bool FileSystem::hasTxtExtension(const std::string& name) {
    return std::filesystem::path(name).extension() == ".txt";
}

int FileSystem::findFileIndex(const std::string& filename) {
    for (int i = 0; i < fileTable.size(); ++i) {
        if (fileTable[i].name == filename) return i;
    }
    return -1;
}

void FileSystem::saveToDisk() {
    std::ofstream outFile(systemFileName, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error saving file system to disk!" << std::endl;
        return;
    }

    int fileTableSize = fileTable.size();
    outFile.write(reinterpret_cast<char*>(&fileTableSize), sizeof(int));
    for (const auto& entry : fileTable) {
        int nameSize = entry.name.size();
        outFile.write(reinterpret_cast<char*>(&nameSize), sizeof(int));
        outFile.write(entry.name.c_str(), nameSize);
        outFile.write(reinterpret_cast<const char*>(&entry.startAddress), sizeof(int));
    }

    int freeBlocksSize = freeBlocks.size();
    outFile.write(reinterpret_cast<char*>(&freeBlocksSize), sizeof(int));
    for (int block : freeBlocks) {
        outFile.write(reinterpret_cast<const char*>(&block), sizeof(int));
    }

    for (const auto& block : dataBlocks) {
        outFile.write(reinterpret_cast<const char*>(&block), sizeof(DataBlock));
    }

    outFile.close();
}

void FileSystem::loadFromDisk() {
    std::ifstream inFile(systemFileName, std::ios::binary);
    if (!inFile) {
        return;
    }

    int fileTableSize=0;
    inFile.read(reinterpret_cast<char*>(&fileTableSize), sizeof(int));
    fileTable.resize(fileTableSize);
    for (int i = 0; i < fileTableSize; ++i) {
        int nameSize;
        inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(int));
        char* nameBuffer = new char[nameSize + 1];
        inFile.read(nameBuffer, nameSize);
        nameBuffer[nameSize] = '\0';
        fileTable[i].name = nameBuffer;
        delete[] nameBuffer;
        inFile.read(reinterpret_cast<char*>(&fileTable[i].startAddress), sizeof(int));
    }

    int freeBlocksSize;
    inFile.read(reinterpret_cast<char*>(&freeBlocksSize), sizeof(int));
    freeBlocks.resize(freeBlocksSize);
    for (int i = 0; i < freeBlocksSize; ++i) {
        inFile.read(reinterpret_cast<char*>(&freeBlocks[i]), sizeof(int));
    }

    dataBlocks.clear();
    while (inFile.peek() != EOF) {
        DataBlock block;
        inFile.read(reinterpret_cast<char*>(&block), sizeof(DataBlock));
        dataBlocks.push_back(block);
    }

    inFile.close();
}

FileSystem::FileSystem() {

    int first_block_size = (1 * 1024 * 1024) / 500;        /// 2,097 sub-blocks (1MB / 500B)
    int data_block_size = (8 * 1024 * 1024) / 1024;        /// 8,192 blocks (8MB / 1024B)

    fileTable.reserve(first_block_size);                   // Reserve space for 2,097 FileEntry structs
    freeBlocks.resize(data_block_size);                   // Reserve space for 8,192 indices
    dataBlocks.resize(data_block_size);                    // Resize to 8,192 DataBlocks




    for (int i = 0; i < data_block_size; ++i)              // Populate freeBlocks with indices 0 to 8191
        freeBlocks[i]=i;
      loadFromDisk();
}

FileSystem::~FileSystem() {
    saveToDisk();
}

bool FileSystem::createNewFile(const std::string& filename, const std::string& fileData, std::string& errorMessage) {
    if (!hasTxtExtension(filename)) {
        errorMessage = "Filename must end with .txt";
        return false;
    }
    if (findFileIndex(filename) != -1) {
        errorMessage = "File already exists!";
        return false;
    }
    if (freeBlocks.empty()) {
        errorMessage = "No free space available!";
        return false;
    }

    int startAddress = freeBlocks.front();
    freeBlocks.erase(freeBlocks.begin());
    int currentAddress = startAddress;

    size_t dataWritten = 0;
    while (dataWritten < fileData.size()) {
        size_t chunkSize = std::min(fileData.size() - dataWritten, sizeof(DataBlock::data) - 1);
        std::copy(fileData.begin() + dataWritten,fileData.begin() + dataWritten + chunkSize,dataBlocks[currentAddress].data);
        dataBlocks[currentAddress].data[chunkSize] = '\0';
        dataWritten += chunkSize;

        if (dataWritten < fileData.size()) {
            if (freeBlocks.empty()) {
                errorMessage = "Not enough space!";
                return false;
            }
            int nextAddr = freeBlocks.front();
            freeBlocks.erase(freeBlocks.begin());
            dataBlocks[currentAddress].nextAddress = nextAddr;
            currentAddress = nextAddr;
        }
        else {
            dataBlocks[currentAddress].nextAddress = -1;
        }
    }

    fileTable.push_back({ filename, startAddress });
    saveToDisk();
    return true;
}

void FileSystem::listAndViewFiles(std::string& output) {
    if (fileTable.empty()) {
        output = "No files in the system.";
        return;
    }


    loadFromDisk();

    output = "Available files:\n";
    for (int i = 0; i < fileTable.size(); ++i) {
        output += std::to_string(i + 1) + ". " + fileTable[i].name + "\n";
    }
}

bool FileSystem::copyFromWindows(const std::string& sourcePath, std::string& errorMessage) {
    if (!hasTxtExtension(sourcePath)) {
        errorMessage = "Only .txt files allowed!";
        return false;
    }

    std::ifstream sourceFile(sourcePath, std::ios::binary);
    if (!sourceFile) {
        errorMessage = "Could not open source file!";
        return false;
    }

    std::string filename = std::filesystem::path(sourcePath).filename().string();
    if (findFileIndex(filename) != -1) {
        errorMessage = "File already exists!";
        sourceFile.close();
        return false;
    }

    std::string fileData((std::istreambuf_iterator<char>(sourceFile)),
        std::istreambuf_iterator<char>());
    sourceFile.close();

    return createNewFile(filename, fileData, errorMessage);
}

bool FileSystem::copyToWindows(int fileIndex, const std::string& destPath, std::string& errorMessage) {
    if (fileIndex < 0 || fileIndex >= static_cast<int>(fileTable.size())) {
        errorMessage = "Invalid file number!";
        return false;
    }

    if (!hasTxtExtension(destPath)) {
        errorMessage = "Destination must end in .txt!";
        return false;
    }

    std::ofstream destFile(destPath, std::ios::binary);
    if (!destFile) {
        errorMessage = "Could not create destination file!";
        return false;
    }

    int addr = fileTable[fileIndex].startAddress;
    while (addr != -1) {
        destFile << dataBlocks[addr].data;
        addr = dataBlocks[addr].nextAddress;
    }
    destFile.close();
    return true;
}

bool FileSystem::modifyFile(int fileIndex, const std::string& newData, std::string& errorMessage) {
    if (fileIndex < 0 || fileIndex >= static_cast<int>(fileTable.size())) {
        errorMessage = "Invalid file number!";
        return false;
    }

    // Find last block of the file
    int currentAddress = fileTable[fileIndex].startAddress;
    while (dataBlocks[currentAddress].nextAddress != -1) {
        currentAddress = dataBlocks[currentAddress].nextAddress;
    }

    // Check if there's space in the last block
    size_t existingDataLength = strlen(dataBlocks[currentAddress].data);
    size_t remainingSpace = sizeof(DataBlock::data) - existingDataLength - 1;

    if (newData.size() <= remainingSpace) {
        // Fits in current block
        std::copy(newData.begin(), newData.end(),dataBlocks[currentAddress].data + existingDataLength);
        dataBlocks[currentAddress].data[existingDataLength + newData.size()] = '\0';
    }
    else {
        // Use remaining space in current block
        std::copy(newData.begin(), newData.begin() + remainingSpace,dataBlocks[currentAddress].data + existingDataLength);
        dataBlocks[currentAddress].data[sizeof(DataBlock::data) - 1] = '\0';
        size_t dataWritten = remainingSpace;

        // Allocate new blocks as needed
        
            if (freeBlocks.empty()) {
                errorMessage = "Not enough space to complete modification!";
                return false;
            }

            int nextAddress = freeBlocks.front();
            freeBlocks.erase(freeBlocks.begin());
            dataBlocks[currentAddress].nextAddress = nextAddress;
            currentAddress = nextAddress;

            size_t chunkSize = newData.size() - dataWritten;
            std::copy(newData.begin() + dataWritten, newData.begin() + dataWritten + chunkSize,
                dataBlocks[currentAddress].data);
            dataBlocks[currentAddress].data[chunkSize] = '\0';
           
        
        dataBlocks[currentAddress].nextAddress = -1;
    }

    saveToDisk();
    return true;
}

bool FileSystem::deleteFile(int fileIndex, std::string& errorMessage) {
    if (fileIndex < 0 || fileIndex >= static_cast<int>(fileTable.size())) {
        errorMessage = "Invalid file number!";
        return false;
    }

    // Free all blocks used by the file
    int currentAddress = fileTable[fileIndex].startAddress;
    while (currentAddress != -1) {
        int nextAddress = dataBlocks[currentAddress].nextAddress;
        freeBlocks.push_back(currentAddress);

       

      
        std::memset(dataBlocks[currentAddress].data, 0, sizeof(DataBlock::data));
        dataBlocks[currentAddress].nextAddress = -1;
        currentAddress = nextAddress;
    }

    // Remove from file table
    fileTable.erase(fileTable.begin() + fileIndex);
    saveToDisk();
    return true;
}

void FileSystem::getFreeBlocks(std::string& output) {
    if (freeBlocks.empty()) {
        output = "No free blocks available.";
        return;
    }

    output = "Free blocks: ";
    size_t count = 0;
    for (int block : freeBlocks) {
        
        output += std::to_string(block) + " ";
    }
}

int FileSystem::getEndAddress(int fileIndex) {
    if (fileIndex < 0 || fileIndex >= static_cast<int>(fileTable.size())) {
        return -1;
    }
    // grab the index of the first block for this file
    int firstBlock = fileTable[fileIndex].startAddress;

    // return its stored 'nextAddress' (or –1 if there's no second block)
    return dataBlocks[firstBlock].nextAddress;
}