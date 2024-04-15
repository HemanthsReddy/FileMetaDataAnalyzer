// file_registry.cpp

// #pragma once

// #include <stb_image.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <vector>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>
#include <cstring>
#include <memory>
#include <cstdint>
#include <type_traits>
#include "file_types.cpp"
#include "additional_metadata_handler.cpp"
// namespace fs = std::filesystem;

// #pragma GCC diagnostic ignored "-std=c++17"

namespace fs = std::filesystem;

extern const FileTypeBase* classtypePtr ;

template <typename FileType>
class FileTypeRegistry {
protected:
    std::vector<std::shared_ptr<FileTypeBase>> fileTypes;
    const std::string &filename;
public:
    // Function to register multiple filetypes
    // Use variadic templates to be able to register any number of filtype with one call.
    template <typename FileType2, typename... OtherFileTypes>
    void registerFileTypes(std::shared_ptr<FileType2> fileType, std::shared_ptr<OtherFileTypes>... otherFileTypes) {
        (fileTypes.push_back(fileType), ..., fileTypes.push_back(otherFileTypes));
    }

    explicit FileTypeRegistry(const std::string &filename) : filename(filename) {}
    // Function to identify the file type based on its magic number
    std::string identifyFileType() {
        std::ifstream file(this->filename, std::ios::binary);
        if (!file) {
            return "unknown";
        }

        // Read the magic number from the file
        std::vector<unsigned char> magicNumber(4); // Assuming magic number is 4 bytes
        file.read(reinterpret_cast<char *>(magicNumber.data()), magicNumber.size());

        // Compare the magic number with registered file types
        for (const auto &fileType : fileTypes) {
            auto magic = fileType->getMagicNumber();
            if (magic.size() <= magicNumber.size() &&
                std::equal(magic.begin(), magic.end(), magicNumber.begin())) {
                // classtype = fileType->getClassType();
                classtypePtr = fileType->getClassType();
                // std::cout<<"magic number"<<std::endl;
                return fileType->getTypeName();
            }
        }

        fs::path filePath(this->filename);
        std::string fileExtension = filePath.extension().string();
        for (const auto &fileType : fileTypes) {
            if (fileType->getFileExtension() == fileExtension) {
                classtypePtr = fileType->getClassType();
                return fileType->getTypeName();
            }
        }

        return "unknown";
    }



    // Function to retrieve the creation time of a file
    // std::string getFileCreationTime(const std::string &filename);
    public:
        std::string getFileCreationTime() {
            // std::cout<<"generic\n";
            struct stat fileInfo;
            if (stat(this->filename.c_str(), &fileInfo) == 0) {
                return std::ctime(&fileInfo.st_mtime);
            } else {
                return "Unknown";
            }
        }

        std::string getFileLastModifiedTime(){
            struct stat fileInfo;
            if (stat(this->filename.c_str(), &fileInfo) == 0)
            {
                return std::ctime(&fileInfo.st_ctime);
            }
            else
            {
                // Handle the case where stat fails
                // For example, you might return "Unknown" or throw an exception
                return "Unknown";
            }
        }
        std::streampos getFileSize(){
            std::ifstream file(this->filename, std::ios::binary | std::ios::ate);
            if (!file)
            {
                return -1; // Error occurred while opening the file
            }
            return file.tellg();
        }

        template<typename... Args>
        std::string concatenate(Args&&... args) {
            std::string result;
            ((result += std::forward<Args>(args)), ...);
            return result;
        }

        std::string checkFilePermissions() {
            fs::file_status status = fs::status(this->filename);
            fs::perms permissions = status.permissions();

            return concatenate(
                ((permissions & fs::perms::owner_read) != fs::perms::none ? "Owner Readable " : ""),
                ((permissions & fs::perms::owner_write) != fs::perms::none ? "Owner Writable " : ""),
                ((permissions & fs::perms::group_read) != fs::perms::none ? "Group Readable " : ""),
                ((permissions & fs::perms::group_write) != fs::perms::none ? "Group Writable " : ""),
                ((permissions & fs::perms::others_read) != fs::perms::none ? "Others Readable " : ""),
                ((permissions & fs::perms::others_write) != fs::perms::none ? "Others Writable " : "")
            );
        }
        std::string getFilePath()
        {
            std::string fullPath = fs::absolute(this->filename).string();
            std::string fileInfo = "File path: " + fullPath;
            return fileInfo;
        }

        template<typename FileType2>
        void handleFileTypeIfDetected(bool isDetected) {
            if (isDetected) {
                FileType2 file;
                AdditionalDataHandler<FileType2> handler;
                handler.handleAdditionalData(file,filename);
            }
        }
};




struct FileMetadata {
        std::string name;
        int size;
        time_t creationTime;
        std::string fileType;
};


template <typename T>
class BinaryFileTypeRegistry : public FileTypeRegistry<T> {
public:
    using FileTypeRegistry<T>::FileTypeRegistry;

    std::vector<FileMetadata> extractMetadataFromBinary() {
        std::vector<FileMetadata> metadata;
        std::ifstream file(this->filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error opening file: " << this->filename << std::endl;
            return metadata;
        }

        // Define a lambda function to read file metadata
        auto readMetadata = [&]() {
            FileMetadata fileMetadata;
            int nameLength;
            file.read(reinterpret_cast<char *>(&nameLength), sizeof(int));
            char* nameBuffer = new char[nameLength + 1];
            file.read(nameBuffer, nameLength);
            nameBuffer[nameLength] = '\0';
            fileMetadata.name = nameBuffer;
            delete[] nameBuffer;
            file.read(reinterpret_cast<char *>(&fileMetadata.size), sizeof(int));
            file.seekg(fileMetadata.size, std::ios::cur);
            file.read(reinterpret_cast<char *>(&fileMetadata.creationTime), sizeof(time_t));
            metadata.push_back(fileMetadata);
        };

        // Read number of files in the binary file
        int numFiles;
        file.read(reinterpret_cast<char *>(&numFiles), sizeof(int));

        // Read creation timestamp of the binary file
        time_t binaryCreationTime;
        file.read(reinterpret_cast<char *>(&binaryCreationTime), sizeof(time_t));

        // Read file metadata for each file
        for (int i = 0; i < numFiles; ++i) {
            readMetadata();
        }

        file.close();
        return metadata;
    }
};



