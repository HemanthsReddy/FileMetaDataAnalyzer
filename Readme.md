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
git clone https://github.com/HemanthsReddy/FileMetaDataAnalyzer
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

## Example Usage
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

## Converting Files to Binary Dump
You can use the provided C++ code to convert multiple files into a single binary file. 

```bash
g++ -std=c++17 Convert_to_binary.cpp -o file_converter
```
```bash
./file_converter
```
After execution, you'll find the binary dump file named "binary_dump.bin" in your directory.

## Reading Binary Dump Files
You can use the provided C++ code to read data from a binary dump file.

## Examples Usage
Analyzing a JPEG image file:

```yaml
Are you entering a bin file? (yes/no): yes
Enter the file path: /Users/sathwik/Desktop/GP/Most_done/FileMetaDataAnalyzer/source/binary_dump2.bin
Number of files: 8
Bin file size: 7460212
Bin file path: File path: /Users/sathwik/Desktop/GP/Most_done/FileMetaDataAnalyzer/source/binary_dump2.bin
Bin file permission: Mon Apr 15 12:41:40 2024
Bin file permission: Mon Apr 15 12:41:40 2024
Bin file permission: Owner Readable Owner Writable Group Readable Others Readable 
File Name: source/123.png
File Size: 558265
Creation Time: Mon Apr 15 12:18:59 2024

File Name: source/AlanWalker.mp3
File Size: 3921013
Creation Time: Mon Apr 15 12:24:30 2024

File Name: source/BetaListProducts_2024-03-31.csv
File Size: 1444
Creation Time: Mon Apr 15 12:19:32 2024

File Name: source/books.xml
File Size: 4429
Creation Time: Mon Apr 15 12:30:49 2024

File Name: source/EffectiveSTL.pdf
File Size: 1905750
Creation Time: Mon Apr 15 12:19:10 2024

File Name: source/Image.jpeg
File Size: 1021962
Creation Time: Mon Apr 15 12:19:17 2024

File Name: source/TeamPengs.docx
File Size: 46568
Creation Time: Mon Apr 15 12:21:29 2024

File Name: source/test.txt
File Size: 476
Creation Time: Mon Apr 15 12:19:04 2024
```


License
This project is licensed under the MIT License.
