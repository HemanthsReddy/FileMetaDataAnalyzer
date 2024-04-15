#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "file_types.cpp"
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


namespace fs = std::filesystem;

template <typename FileType>
class AdditionalDataHandler {
public:
    // Member function for handling additional data
    void handleAdditionalData(const FileType& fileType, const std::string & filepath) const {
        std::cout << "Additional data for " << fileType.getTypeName() << ": Not implemented" << std::endl;
    }
};

template <>
class AdditionalDataHandler<TXTFileType> {
public:
    // Member function for handling additional data specific to JPEGFileType
    void handleAdditionalData(const TXTFileType& fileType, const std::string & filepath) const {
        std::cout << "Additional data for JPEG: JPEG specific operation" << std::endl;

        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filepath << std::endl;
            return;
        }

        std::string line;
        int numLines = 0;
        int numWords = 0;

        while (std::getline(file, line)) {
            numLines++;

            // Using stringstream to extract words from each line
            std::istringstream iss(line);
            std::string word;
            while (iss >> word) {
                numWords++;
            }
        }

        file.close();

        // Print the results
        std::cout << "Number of lines: " << numLines << std::endl;
        std::cout << "Number of words: " << numWords << std::endl;
        
    }
};


// Declaration of readCSVHeader function
bool readCSVHeader(const std::string& filename, std::vector<std::string>& header);

// Template specialization for AdditionalDataHandler<CSVFileType>
template <>
class AdditionalDataHandler<CSVFileType> {
public:
    // Member function for handling additional data specific to PDFFileType
    void handleAdditionalData(const CSVFileType& fileType, const std::string & filepath) const {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filepath << std::endl;
            return ;
        }

        std::string line;
        if (!std::getline(file, line)) {
            std::cerr << "Failed to read header from file: " << filepath << std::endl;
            file.close();
            return ;
        }

        std::istringstream iss(line);
        std::string field;
        std::cout << "Header fields:" << std::endl;
        while (std::getline(iss, field, ',')) {
            std::cout << "  " << field << std::endl;
        }

        file.close();
        return ;
    }
};



// Template specialization for PNGFileType
struct ImageMetadata {
    int width;
    int height;
    int channels;
    std::string format;
};

// Define the AdditionalDataHandler class for PNGFileType
template <>
class AdditionalDataHandler<PNGFileType> {
public:
    // Member function to get image metadata
    ImageMetadata getImageMetadata(const std::string& filename) const {
        ImageMetadata metadata;
        metadata.width = 0;
        metadata.height = 0;
        metadata.channels = 0;
        metadata.format = "";

        int width, height, channels;
        unsigned char* image = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb);

        if (image != nullptr) {
            metadata.width = width;
            metadata.height = height;
            metadata.channels = channels;

            // Determine the image format based on the number of channels
            switch (channels) {
                case 1:
                    metadata.format = "Grayscale";
                    break;
                case 3:
                    metadata.format = "RGB";
                    break;
                case 4:
                    metadata.format = "RGBA";
                    break;
                default:
                    metadata.format = "Unknown";
                    break;
            }

            stbi_image_free(image); // Free the image data
        } else {
            std::cerr << "Failed to load image: " << filename << std::endl;
        }

        return metadata;
    }

    // Member function to handle additional data for PNG files
    void handleAdditionalData(const PNGFileType& fileType, const std::string& filename) const {
        // Get image metadata
        ImageMetadata metadata = getImageMetadata(filename);

        // Print image metadata
        std::cout << "Image Metadata:" << std::endl;
        std::cout << "Width: " << metadata.width << " pixels" << std::endl;
        std::cout << "Height: " << metadata.height << " pixels" << std::endl;
        std::cout << "Channels: " << metadata.channels << std::endl;
        std::cout << "Format: " << metadata.format << std::endl;
    }
};

template <>
class AdditionalDataHandler<JPEGFileType> {
public:
    // Member function to get image metadata
    ImageMetadata getImageMetadata(const std::string& filename) const {
        ImageMetadata metadata;
        metadata.width = 0;
        metadata.height = 0;
        metadata.channels = 0;
        metadata.format = "";

        int width, height, channels;
        unsigned char* image = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb);

        if (image != nullptr) {
            metadata.width = width;
            metadata.height = height;
            metadata.channels = channels;

            // Determine the image format based on the number of channels
            switch (channels) {
                case 1:
                    metadata.format = "Grayscale";
                    break;
                case 3:
                    metadata.format = "RGB";
                    break;
                case 4:
                    metadata.format = "RGBA";
                    break;
                default:
                    metadata.format = "Unknown";
                    break;
            }

            stbi_image_free(image); // Free the image data
        } else {
            std::cerr << "Failed to load image: " << filename << std::endl;
        }

        return metadata;
    }

    // Member function to handle additional data for PNG files
    void handleAdditionalData(const JPEGFileType& fileType, const std::string& filename) const {
        // Get image metadata
        ImageMetadata metadata = getImageMetadata(filename);

        // Print image metadata
        std::cout << "Image Metadata:" << std::endl;
        std::cout << "Width: " << metadata.width << " pixels" << std::endl;
        std::cout << "Height: " << metadata.height << " pixels" << std::endl;
        std::cout << "Channels: " << metadata.channels << std::endl;
        std::cout << "Format: " << metadata.format << std::endl;
    }
};

