# File Metadata Analyzer
The File Metadata Analyzer is a C++ program designed to analyze various types of files and extract metadata such as file type, creation time, file size, and permissions. It supports a variety of file types including JPEG, PNG, PDF, DOCX, MP3, MP4, XML, CSV, and TXT.

## Features
Identification of file types based on magic numbers and file extensions.
Extraction of creation time, last modified time, and file size.
Analysis of file permissions.
Specialized handling for specific file types including text files (TXT) and CSV files.
## Dependencies
STB Image - For loading images.
C++ Filesystem Library - For file and directory manipulation.

## Installation
Clone the repository:
```bash
git clone <repository_url>
```

## Compile the program using a C++ compiler (e.g., g++):
```bash
g++ --std=c++20 final_project.cpp -o file_metadata_analyzer
```

## Run the executable:
``` bash
./file_metadata_analyzer

```
## Usage

When prompted, enter the file path of the file you want to analyze.
The program will display the file type, creation time, file size, last modified time, and file permissions.
If the file is a binary file, it will extract metadata for each file contained within the binary.
Specialized handling is provided for specific file types such as text files and CSV files.

## Examples
Analyzing a JPEG image file:

```yaml
Are you entering a bin file? (yes/no): no
Enter the file path: source/123.png
File type: PNG
File Path: File path: /full_path/source/123.png
Size: 558265
Creation time: Mon Apr 15 12:41:40 2024
Last modified time: Mon Apr 15 12:41:40 2024
File permissions: Owner Readable Owner Writable Group Readable Others Readable 
Image Metadata:
Width: 562 pixels
Height: 684 pixels
Channels: 4
Format: RGBA
```

# Converting Files to Binary Dump
You can use the provided C++ code to convert multiple files into a single binary file. 

```bash
g++ -std=c++17 Convert_to_binary.cpp -o file_converter
```
```bash
./file_converter
```
After execution, you'll find the binary dump file named "binary_dump.bin" in your directory.





License
This project is licensed under the MIT License.
