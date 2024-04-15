
// main.cpp


#include "file_type_registry.cpp"
// #include "additional_metadata_handler.cpp"
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
// #include <stb_image.h>
// namespace fs = std::filesystem;

namespace fs = std::filesystem;

const FileTypeBase* classtypePtr = nullptr;

template<typename T>
struct is_FileType : std::is_base_of<FileTypeBase, T> {};


template<typename FileType, typename T>
bool isSpecificFileType(const T* objPtr) {
    const FileType* castedPtr = dynamic_cast<const FileType*>(objPtr);
    return castedPtr != nullptr;
}


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
            std::cout << "File type: " << fileType<< std::endl;

            // Assuming *classtypePtr returns a pointer to an object
            // bool isCSVFile = std::is_same<std::remove_pointer<decltype(*classtypePtr)>::type, CSVFileType>::value;
            // bool isCSVFile = (typeid(*classtypePtr) == typeid(CSVFileType));

            // FileTypeBase file ;

            // fileTypeRegistry.handleFileTypeIfDetected<CSVFileType>(isSpecificFileType<CSVFileType>(classtypePtr));
            // fileTypeRegistry.handleFileTypeIfDetected<XMLFileType>(isSpecificFileType<XMLFileType>(classtypePtr));
            // fileTypeRegistry.handleFileTypeIfDetected<PDFFileType>(isSpecificFileType<PDFFileType>(classtypePtr));
    
            std::string fileInfo = fileTypeRegistry.getFilePath();
            std::cout << "File Path: "<<fileInfo << std::endl;
            std::string creationTime = fileTypeRegistry.getFileCreationTime();
            std::cout<<"Size: "<<fileTypeRegistry.getFileSize()<<std::endl;
            std::cout << "Creation time: " << creationTime;
            std::string modifiedTime = fileTypeRegistry.getFileLastModifiedTime();
            std::cout << "Last modified time: " << modifiedTime;
            std::string permissions = fileTypeRegistry.checkFilePermissions();
            std::cout << "File permissions: " << permissions << std::endl;
            fileTypeRegistry.handleFileTypeIfDetected<CSVFileType>(isSpecificFileType<CSVFileType>(classtypePtr));
            fileTypeRegistry.handleFileTypeIfDetected<TXTFileType>(isSpecificFileType<TXTFileType>(classtypePtr));
            fileTypeRegistry.handleFileTypeIfDetected<PNGFileType>(isSpecificFileType<PNGFileType>(classtypePtr));
            fileTypeRegistry.handleFileTypeIfDetected<JPEGFileType>(isSpecificFileType<JPEGFileType>(classtypePtr));
            fileTypeRegistry.handleFileTypeIfDetected<PDFFileType>(isSpecificFileType<PDFFileType>(classtypePtr));
            fileTypeRegistry.handleFileTypeIfDetected<MP3FileType>(isSpecificFileType<MP3FileType>(classtypePtr));
            fileTypeRegistry.handleFileTypeIfDetected<MP4FileType>(isSpecificFileType<MP4FileType>(classtypePtr));
            fileTypeRegistry.handleFileTypeIfDetected<XMLFileType>(isSpecificFileType<XMLFileType>(classtypePtr));
            fileTypeRegistry.handleFileTypeIfDetected<DOCXFileType>(isSpecificFileType<DOCXFileType>(classtypePtr));
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

