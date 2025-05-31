#include "MyForm.h"
#include <msclr/marshal_cppstd.h>

namespace semprojectdsa {

    void MyForm::UpdateFileDisplay(const std::string& filename, int startAddress, const std::string& content, int endAddress) {
        // Shift existing entries down
        textBoxFilename4->Text = textBoxFilename3->Text;
        textBoxFilename3->Text = textBoxFilename2->Text;
        textBoxFilename2->Text = textBoxFilename1->Text;
        textBoxFilename1->Text = gcnew String(filename.c_str());

        textBoxStartAddr4->Text = textBoxStartAddr3->Text;
        textBoxStartAddr3->Text = textBoxStartAddr2->Text;
        textBoxStartAddr2->Text = textBoxStartAddr1->Text;
        textBoxStartAddr1->Text = startAddress.ToString();

        textBoxContent4->Text = textBoxContent3->Text;
        textBoxContent3->Text = textBoxContent2->Text;
        textBoxContent2->Text = textBoxContent1->Text;
        textBoxContent1->Text = gcnew String(content.substr(0, 50).c_str()); // Limit content to 50 chars

        textBoxEndAddr4->Text = textBoxEndAddr3->Text;
        textBoxEndAddr3->Text = textBoxEndAddr2->Text;
        textBoxEndAddr2->Text = textBoxEndAddr1->Text;
        textBoxEndAddr1->Text = endAddress.ToString();
    }

    void MyForm::ClearFileDisplay() {
        textBoxFilename1->Clear();
        textBoxFilename2->Clear();
        textBoxFilename3->Clear();
        textBoxFilename4->Clear();
        textBoxStartAddr1->Clear();
        textBoxStartAddr2->Clear();
        textBoxStartAddr3->Clear();
        textBoxStartAddr4->Clear();
        textBoxContent1->Clear();
        textBoxContent2->Clear();
        textBoxContent3->Clear();
        textBoxContent4->Clear();
        textBoxEndAddr1->Clear();
        textBoxEndAddr2->Clear();
        textBoxEndAddr3->Clear();
        textBoxEndAddr4->Clear();
    }

    System::Void MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
        // Convert System::String^ to std::string
        std::string filename = msclr::interop::marshal_as<std::string>(textBox1->Text);
        std::string fileData = msclr::interop::marshal_as<std::string>(richTextBox1->Text);
        std::string errorMessage;

        if (filename.empty()) {
            MessageBox::Show("Please enter a file name.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (fileSystem->createNewFile(filename, fileData, errorMessage)) {
            MessageBox::Show("File created successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            int fileIndex = fileSystem->findFileIndex(filename);
            int endAddress = fileSystem->getEndAddress(fileIndex);
            UpdateFileDisplay(filename,fileSystem->fileTable[fileIndex].startAddress, fileData, endAddress);
            textBox1->Clear();
            richTextBox1->Clear();
        }
        else {
            MessageBox::Show(gcnew String(errorMessage.c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e) {
        std::string output;
        fileSystem->listAndViewFiles(output);
        richTextBox1->Text = gcnew String(output.c_str());

        std::string freeBlocks;
        fileSystem->getFreeBlocks(freeBlocks);
        richTextBoxFreeSpaces->Text = gcnew String(freeBlocks.c_str());
    }

    System::Void MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e) {
        std::string sourcePath = msclr::interop::marshal_as<std::string>(textBox1->Text);
        std::string errorMessage;

        if (sourcePath.empty()) {
            MessageBox::Show("Please enter a source file path.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (fileSystem->copyFromWindows(sourcePath, errorMessage)) {
            MessageBox::Show("File copied successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            std::string filename = std::filesystem::path(sourcePath).filename().string();
            int fileIndex = fileSystem->findFileIndex(filename);
            std::ifstream sourceFile(sourcePath, std::ios::binary);
            std::string fileData((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
            sourceFile.close();
            int endAddress = fileSystem->getEndAddress(fileIndex);
            UpdateFileDisplay(filename, fileSystem->fileTable[fileIndex].startAddress, fileData, endAddress);
            textBox1->Clear();
        }
        else {
            MessageBox::Show(gcnew String(errorMessage.c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void MyForm::button4_Click(System::Object^ sender, System::EventArgs^ e) {
        std::string input = msclr::interop::marshal_as<std::string>(textBox1->Text);
        std::string errorMessage;

        if (input.empty()) {
            MessageBox::Show("Please enter a file number.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        try {
            int fileNumber = std::stoi(input) - 1; // Convert to zero-based index
            if (fileSystem->deleteFile(fileNumber, errorMessage)) {
                MessageBox::Show("File deleted successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                ClearFileDisplay(); // Clear display as file is deleted
                textBox1->Clear();
                richTextBox1->Clear();
            }
            else {
                MessageBox::Show(gcnew String(errorMessage.c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        catch (const std::exception&) {
            MessageBox::Show("Invalid file number!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void MyForm::button5_Click(System::Object^ sender, System::EventArgs^ e) {
        std::string input = msclr::interop::marshal_as<std::string>(textBox1->Text);
        std::string newData = msclr::interop::marshal_as<std::string>(richTextBox1->Text);
        std::string errorMessage;

        if (input.empty()) {
            MessageBox::Show("Please enter a file number.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (newData.empty()) {
            MessageBox::Show("Please enter content to append.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        try {
            int fileNumber = std::stoi(input) - 1; // Convert to zero-based index
            if (fileSystem->modifyFile(fileNumber, newData, errorMessage)) {
                MessageBox::Show("File modified successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                std::string filename = fileSystem->fileTable[fileNumber].name;
                int endAddress = fileSystem->getEndAddress(fileNumber);
                UpdateFileDisplay(filename, fileSystem->fileTable[fileNumber].startAddress, newData, endAddress);
                textBox1->Clear();
                richTextBox1->Clear();
            }
            else {
                MessageBox::Show(gcnew String(errorMessage.c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        catch (const std::exception&) {
            MessageBox::Show("Invalid file number!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void MyForm::button6_Click(System::Object^ sender, System::EventArgs^ e) {
        std::string input = msclr::interop::marshal_as<std::string>(textBox1->Text);
        std::string destPath = msclr::interop::marshal_as<std::string>(textBox2->Text);
        std::string errorMessage;

        if (input.empty()) {
            MessageBox::Show("Please enter a file number.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (destPath.empty()) {
            MessageBox::Show("Please enter a destination path.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        try {
            int fileNumber = std::stoi(input) - 1; // Convert to zero-based index
            if (fileSystem->copyToWindows(fileNumber, destPath, errorMessage)) {
                MessageBox::Show("File copied to Windows successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                textBox1->Clear();
                textBox2->Clear();
            }
            else {
                MessageBox::Show(gcnew String(errorMessage.c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        catch (const std::exception&) {
            MessageBox::Show("Invalid file number!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}