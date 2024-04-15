// file_types.cpp

#pragma once
// #pragma GCC diagnostic ignored "-std=c++17"
#include <string>
#include <vector>

// Define a base class for file types
class FileTypeBase {
public:
    virtual ~FileTypeBase() {}
    virtual std::string getTypeName() const = 0;
    virtual std::vector<unsigned char> getMagicNumber() const = 0;
    virtual FileTypeBase* getClassType() const = 0;
    virtual std::string getFileExtension() const = 0;
    virtual int getmagicsize() const = 0;
};

// Define concrete classes for different file types (JPEG, PNG, PDF, etc.)
// Implementations go here...

extern const FileTypeBase* classtypePtr ;

// Define a concrete class for JPEG file type
class JPEGFileType : public FileTypeBase {
public:
    std::string getTypeName() const override {
        return "JPEG";
    }

    std::vector<unsigned char> getMagicNumber() const override {
        return {0xFF, 0xD8, 0xFF};
    }

    FileTypeBase* getClassType() const override {
        return new JPEGFileType(); // Return pointer to PDFFileType
    }

    std::string getFileExtension() const override {
        return ".jpg";
    }

    int getmagicsize() const override{
        return 4;
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

    FileTypeBase* getClassType() const override {
        return new PNGFileType(); // Return pointer to PDFFileType
    }

    std::string getFileExtension() const override {
        return ".png";
    }

    int getmagicsize() const override{
        return 4;
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

    FileTypeBase* getClassType() const override {
        return new PDFFileType(); // Return pointer to PDFFileType
    }

    std::string getFileExtension() const override {
        return ".pdf";
    }

    int getmagicsize() const override{
        return 4;
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

    FileTypeBase* getClassType() const override {
        return new DOCXFileType(); // Return pointer to PDFFileType
    }

    std::string getFileExtension() const override {
        return ".docx";
    }

    int getmagicsize() const override{
        return 4;
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

    FileTypeBase* getClassType() const override {
        return new MP3FileType(); // Return pointer to PDFFileType
    }

    std::string getFileExtension() const override {
        return ".mp3";
    }

    int getmagicsize() const override{
        return 4;
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

    FileTypeBase* getClassType() const override {
        return new MP4FileType(); // Return pointer to PDFFileType
    }

    std::string getFileExtension() const override {
        return ".mp4";
    }

    int getmagicsize() const override{
        return 8;
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

    FileTypeBase* getClassType() const override {
        return new XMLFileType(); // Return pointer to PDFFileType
    }

    std::string getFileExtension() const override {
        return ".xml";
    }

    int getmagicsize() const override{
        return 5;
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

    FileTypeBase* getClassType() const override {
        return new CSVFileType(); // Return pointer to PDFFileType
    }

    std::string getFileExtension() const override {
        return ".csv";
    }

    int getmagicsize() const override{
        return 10;
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

    FileTypeBase* getClassType() const override {
        return new TXTFileType(); // Return pointer to PDFFileType
    }

    std::string getFileExtension() const override {
        return ".txt";
    }

    int getmagicsize() const override{
        return 4;
    }
};

