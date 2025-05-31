#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include<fstream>

struct FileEntry {
    std::string name;
    int startAddress;
};

struct DataBlock {
    char data[1019]; 
    int nextAddress = -1; // -1 means no next block
};

class FileSystem {
public:
    std::vector<FileEntry> fileTable;    // Metadata
    std::vector<int> freeBlocks;         // Free-block list
    std::vector<DataBlock> dataBlocks;   // Data storage
    const std::string systemFileName = "File_system.dat";

    bool hasTxtExtension(const std::string& name);
    void saveToDisk();
    void loadFromDisk();

    FileSystem();
    ~FileSystem();
    bool createNewFile(const std::string& filename, const std::string& fileData, std::string& errorMessage);
    void listAndViewFiles(std::string& output);
    bool copyFromWindows(const std::string& sourcePath, std::string& errorMessage);
    bool copyToWindows(int fileIndex, const std::string& destPath, std::string& errorMessage);
    bool modifyFile(int fileIndex, const std::string& newData, std::string& errorMessage);
    bool deleteFile(int fileIndex, std::string& errorMessage);
    void getFreeBlocks(std::string& output);
    int getEndAddress(int fileIndex);
    int findFileIndex(const std::string& filename);

};