#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <ctime>
#include <sys/stat.h> // Include sys/stat.h for the stat structure
using namespace std;

// Struct to hold image metadata
struct ImageMetadata {
    string name;
    int size;
    time_t creationTime;
};

// Function to get creation time of a file
time_t getFileCreationTime(const string& filename) {
    struct stat attrib;
    if (stat(filename.c_str(), &attrib) == 0) {
        return attrib.st_ctime;
    } else {
        cerr << "Error getting creation time of file: " << filename << endl;
        return -1;
    }
}

// Function to convert files into a single binary file
void filesToBinaryDump(const vector<string>& files, const string& outputFileName) {
    ofstream outFile(outputFileName, ios::binary);
    if (!outFile) {
        cerr << "Error opening output file: " << outputFileName << endl;
        return;
    }

    // Write number of files in the binary file
    int numFiles = files.size();
    outFile.write(reinterpret_cast<const char*>(&numFiles), sizeof(int));

    // Write creation timestamp of the binary file
    time_t currentTime = time(nullptr);
    outFile.write(reinterpret_cast<const char*>(&currentTime), sizeof(time_t));

    // Write file metadata for each file
    for (const auto& filename : files) {
        // Write file name length and name itself
        int nameLength = filename.length();
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(int));
        outFile.write(filename.c_str(), nameLength);

        // Write file size
        ifstream inFile(filename, ios::binary | ios::ate);
        if (!inFile) {
            cerr << "Error opening input file: " << filename << endl;
            continue;
        }
        int fileSize = inFile.tellg();
        outFile.write(reinterpret_cast<const char*>(&fileSize), sizeof(int));

        // Write file content
        inFile.seekg(0);
        outFile << inFile.rdbuf();

        // Write file creation time
        time_t creationTime = getFileCreationTime(filename);
        if (creationTime == -1) {
            cerr << "Error getting creation time of file: " << filename << endl;
            continue;
        }
        outFile.write(reinterpret_cast<const char*>(&creationTime), sizeof(time_t));

        inFile.close();
    }

    outFile.close();
}

int main() {
    // List of files to be included in the binary file
    vector<string> files = {"source/123.png", "source/AlanWalker.mp3","source/BetaListProducts_2024-03-31.csv","source/books.xml","source/EffectiveSTL.pdf", "source/TeamPengs.docx","source/test.txt"};

    // Output binary file name
    string outputFileName = "binary_dump2.bin";

    // Convert files to binary dump
    filesToBinaryDump(files, outputFileName);
    cout << "Binary dump file '" << outputFileName << "' has been created." << endl;

    return 0;
}
