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

namespace fs = std::filesystem;

// Define a base class for file types
class FileTypeBase {
public:
    virtual ~FileTypeBase() {}
    virtual std::string getTypeName() const = 0;
    virtual std::vector<unsigned char> getMagicNumber() const = 0;
};

// Define a concrete class for JPEG file type
class JPEGFileType : public FileTypeBase {
public:
    std::string getTypeName() const override {
        return "JPEG";
    }

    std::vector<unsigned char> getMagicNumber() const override {
        return {0xFF, 0xD8, 0xFF};
    }
};

// Define a concrete class for PNG file type
class PNGFileType : public FileTypeBase {
public:
    std::string getTypeName() const override {
        return "PNG";
    }

    std::vector<unsigned char> getMagicNumber() const override {
        return {0x89, 0x50, 0x4E, 0x47};
    }
};

class PDFFileType : public FileTypeBase {
public:
    std::string getTypeName() const override {
        return "PDF";
    }

    std::vector<unsigned char> getMagicNumber() const override {
        return {0x25, 0x50, 0x44, 0x46};
    }
};

class DOCXFileType : public FileTypeBase {
public:
    std::string getTypeName() const override {
        return "DOCX";
    }

    std::vector<unsigned char> getMagicNumber() const override {
        return {0x50, 0x4B, 0x03, 0x04};
    }
};

class MP3FileType : public FileTypeBase {
public:
    std::string getTypeName() const override {
        return "MP3";
    }

    std::vector<unsigned char> getMagicNumber() const override {
        return {0x49, 0x44, 0x33};
    }
};

class MP4FileType : public FileTypeBase {
public:
    std::string getTypeName() const override {
        return "MP4";
    }

    std::vector<unsigned char> getMagicNumber() const override {
        return {0x00, 0x00, 0x00, 0x18, 0x66, 0x74, 0x79, 0x70};
    }
};

class XMLFileType : public FileTypeBase {
public:
    std::string getTypeName() const override {
        return "XML";
    }

    std::vector<unsigned char> getMagicNumber() const override {
        return {0x3C, 0x3F, 0x78, 0x6D, 0x6C};
    }
};

class CSVFileType : public FileTypeBase {
public:
    std::string getTypeName() const override {
        return "CSV";
    }

    std::vector<unsigned char> getMagicNumber() const override {
        return {0x2C, 0x22, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x22};
    }
};

class TXTFileType : public FileTypeBase {
public:
    std::string getTypeName() const override {
        return "TXT";
    }

    std::vector<unsigned char> getMagicNumber() const override {
        return {0x20};
    }
};



// Define a template class to manage file type definitions
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
            return "Unknown";
        }

        // Read the magic number from the file
        std::vector<unsigned char> magicNumber(4); // Assuming magic number is 4 bytes
        file.read(reinterpret_cast<char *>(magicNumber.data()), magicNumber.size());

        // Compare the magic number with registered file types
        for (const auto &fileType : fileTypes) {
            auto magic = fileType->getMagicNumber();
            if (magic.size() <= magicNumber.size() &&
                std::equal(magic.begin(), magic.end(), magicNumber.begin())) {
                return fileType->getTypeName();
            }
        }

        return "Unknown";
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


int main() {
    // Create instances of file type classes
    auto jpegFileType = std::make_shared<JPEGFileType>();
    auto pngFileType = std::make_shared<PNGFileType>();
    auto pdfFileType = std::make_shared<PDFFileType>();
    auto docxFileType = std::make_shared<DOCXFileType>();
    auto mp3FileType = std::make_shared<MP3FileType>();
    auto mp4FileType = std::make_shared<MP4FileType>();
    auto xmlFileType = std::make_shared<XMLFileType>();
    auto csvFileType = std::make_shared<CSVFileType>();
    auto txtFileType = std::make_shared<TXTFileType>();
    // Prompt the user to enter the file path
    std::cout << "Are you entering a bin file? (yes/no): ";
    std::string response;
    std::cin >> response;
    std::string filepath;
    std::cout << "Enter the file path: ";
    std::cin >> filepath;
    bool isBinFile = (response == "yes");
    if (fs::is_regular_file(filepath)) {
        if (isBinFile) {
            BinaryFileTypeRegistry<FileTypeBase> binaryFileTypeRegistry(filepath);
            binaryFileTypeRegistry.registerFileTypes<JPEGFileType,PNGFileType,PDFFileType, DOCXFileType,MP3FileType,MP4FileType,XMLFileType,CSVFileType,TXTFileType>(jpegFileType, pngFileType, pdfFileType,docxFileType, mp3FileType, mp4FileType,xmlFileType,csvFileType,txtFileType);
            std::vector<FileMetadata> binaryMetadata = binaryFileTypeRegistry.extractMetadataFromBinary();
            std::cout<<"Number of files: "<<binaryMetadata.size()<<std::endl;
            std::cout<<"Bin file size: "<<binaryFileTypeRegistry.getFileSize()<<std::endl;
            std::cout<<"Bin file path: "<<binaryFileTypeRegistry.getFilePath()<<std::endl;
            std::cout<<"Bin file permission: "<<binaryFileTypeRegistry.getFileCreationTime();
            std::cout<<"Bin file permission: "<<binaryFileTypeRegistry.getFileLastModifiedTime();
            std::cout<<"Bin file permission: "<<binaryFileTypeRegistry.checkFilePermissions()<<std::endl;
            
            for (int i = 0; i < binaryMetadata.size(); ++i) {
                std::cout << "File Name: " << binaryMetadata[i].name << std::endl;
                std::cout << "File Size: " << binaryMetadata[i].size << std::endl;
                std::cout << "Creation Time: " << std::ctime(&binaryMetadata[i].creationTime);
                std::cout << std::endl;
            }
        }
        else {
            FileTypeRegistry<FileTypeBase> fileTypeRegistry(filepath);
            fileTypeRegistry.registerFileTypes<JPEGFileType,PNGFileType,PDFFileType,DOCXFileType,MP3FileType,MP4FileType,XMLFileType,CSVFileType,TXTFileType>(jpegFileType, pngFileType, pdfFileType,docxFileType, mp3FileType, mp4FileType,xmlFileType,csvFileType,txtFileType);
            std::string fileType = fileTypeRegistry.identifyFileType();
            std::cout << "File type: " << fileType << std::endl;
            std::string fileInfo = fileTypeRegistry.getFilePath();
            std::cout << "File Path: "<<fileInfo << std::endl;
            std::string creationTime = fileTypeRegistry.getFileCreationTime();
            std::cout<<"Size: "<<fileTypeRegistry.getFileSize()<<std::endl;
            std::cout << "Creation time: " << creationTime;
            std::string modifiedTime = fileTypeRegistry.getFileLastModifiedTime();
            std::cout << "Last modified time: " << modifiedTime;
            std::string permissions = fileTypeRegistry.checkFilePermissions();
            std::cout << "File permissions: " << permissions << std::endl;
        } 
    }
    else if (fs::is_directory(filepath)){
        std::cout << "It's a directory." << std::endl;
    }
    else {
        std::cout << "Path does not exist." << std::endl;
        return 1;
    }
    return 0;
}
