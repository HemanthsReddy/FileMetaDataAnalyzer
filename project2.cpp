#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <vector>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>
namespace fs = std::filesystem;

// Define a structure to hold file type information
template <typename FileType>
struct FileTypeDefinition
{
    std::string name;
    std::vector<unsigned char> magicNumber;
};

// Define a template class to manage file type definitions
template <typename FileType>
class FileTypeRegistry
{
private:
    std::vector<FileTypeDefinition<FileType>> fileTypes;

public:
    // Function to register file type definitions
    void registerFileType(const std::string &name, const std::vector<unsigned char> &magicNumber)
    {
        fileTypes.push_back({name, magicNumber});
    }

    // Function to identify the file type based on its magic number
    std::string identifyFileType(const std::string &filename)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file)
        {
            return "Unknown";
        }

        // Read the magic number from the file
        std::vector<unsigned char> magicNumber(4); // Assuming magic number is 4 bytes
        file.read(reinterpret_cast<char *>(magicNumber.data()), magicNumber.size());

        // Compare the magic number with registered file types
        for (const auto &fileType : fileTypes)
        {
            if (fileType.magicNumber.size() <= magicNumber.size() &&
                std::equal(fileType.magicNumber.begin(), fileType.magicNumber.end(), magicNumber.begin()))
            {
                return fileType.name;
            }
        }

        return "Unknown";
    }

    std::streampos getFileSize(const std::string &filename)
    {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file)
        {
            return -1; // Error occurred while opening the file
        }
        return file.tellg();
    }

    std::string checkFilePermissions(const std::string &filename)
    {
        fs::file_status status = fs::status(filename);
        fs::perms permissions = status.permissions();

        std::string permissionsStr;

        // Check if the file is readable by owner
        if ((permissions & fs::perms::owner_read) != fs::perms::none)
        {
            permissionsStr += "Readable ";
        }

        // Check if the file is writable by owner
        if ((permissions & fs::perms::owner_write) != fs::perms::none)
        {
            permissionsStr += "Writable ";
        }

        // Check if the file is readable by group
        if ((permissions & fs::perms::group_read) != fs::perms::none)
        {
            permissionsStr += "Group Readable ";
        }

        // Check if the file is writable by group
        if ((permissions & fs::perms::group_write) != fs::perms::none)
        {
            permissionsStr += "Group Writable ";
        }

        // Check if the file is readable by others
        if ((permissions & fs::perms::others_read) != fs::perms::none)
        {
            permissionsStr += "Others Readable ";
        }

        // Check if the file is writable by others
        if ((permissions & fs::perms::others_write) != fs::perms::none)
        {
            permissionsStr += "Others Writable ";
        }

        return permissionsStr;
    }

    std::string getFilePath(const std::string &filepath)
    {
        std::string fullPath = fs::absolute(filepath).string();
        std::string fileInfo = "File path: " + fullPath;
        return fileInfo;
    }

    std::string getFileLastModifiedTime(const std::string &filename)
    {
        struct stat fileInfo;
        if (stat(filename.c_str(), &fileInfo) == 0)
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

    std::string getFileCreationTime(const std::string &filename)
    {
        struct stat fileInfo;
        if (stat(filename.c_str(), &fileInfo) == 0)
        {
            return std::ctime(&fileInfo.st_mtime);
        }
        else
        {
            // Handle the case where stat fails
            // For example, you might return "Unknown" or throw an exception
            return "Unknown";
        }
    }
};

int main()
{
    // Create an instance of the FileTypeRegistry class with a specific file type
    FileTypeRegistry<int> fileTypeRegistry;

    // Register file type definitions
    fileTypeRegistry.registerFileType("JPEG", {0xFF, 0xD8, 0xFF});
    fileTypeRegistry.registerFileType("PNG", {0x89, 0x50, 0x4E, 0x47});
    fileTypeRegistry.registerFileType("PDF", {0x25, 0x50, 0x44, 0x46});
    fileTypeRegistry.registerFileType("DOCX", {0x50, 0x4B, 0x03, 0x04});
    fileTypeRegistry.registerFileType("MP3", {0x49, 0x44, 0x33});
    fileTypeRegistry.registerFileType("MP4", {0x00, 0x00, 0x00, 0x18, 0x66, 0x74, 0x79, 0x70});
    fileTypeRegistry.registerFileType("XML", {0x3C, 0x3F, 0x78, 0x6D, 0x6C});
    fileTypeRegistry.registerFileType("CSV", {0x2C, 0x22, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x22});
    fileTypeRegistry.registerFileType("TXT", {0x20});

    // Add more file types and their magic numbers as needed

    // Prompt the user to enter the file path
    std::string filepath;
    std::cout << "Enter the file path: ";
    std::cin >> filepath;

    if (fs::is_regular_file(filepath))
    {
        std::string fileType = fileTypeRegistry.identifyFileType(filepath);
        std::cout << "File type: " << fileType << std::endl;

        std::streampos fileSize = fileTypeRegistry.getFileSize(filepath);
        if (fileSize != -1)
        {
            std::cout << "File size: " << fileSize << " bytes" << std::endl;
        }
        else
        {
            std::cout << "Failed to get the file size." << std::endl;
        }

        std::string permissions = fileTypeRegistry.checkFilePermissions(filepath);
        std::cout << "File permissions: " << permissions << std::endl;

        std::string fileInfo = fileTypeRegistry.getFilePath(filepath);
        std::cout << fileInfo << std::endl;

        std::string creationTime = fileTypeRegistry.getFileCreationTime(filepath);
        std::cout << "Creation time: " << creationTime<<std::endl;

        std::string modifiedTime = fileTypeRegistry.getFileLastModifiedTime(filepath);
        std::cout << "Last modified time: " << modifiedTime<<std::endl;
    }
    else if (fs::is_directory(filepath))
    {
        std::cout << "It's a directory." << std::endl;
    }
    else
    {
        std::cout << "Path does not exist." << std::endl;
        return 1;
    }

    return 0;
}
