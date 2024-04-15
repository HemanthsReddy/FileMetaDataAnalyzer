# File Metadata Analyzer
The File Metadata Analyzer, written in C++, employs a multitude of programming concepts to analyze diverse file types and extract metadata efficiently. Utilizing Object-Oriented Programming (OOP), the program structures its functionality around classes and objects, including templates to ensure flexibility and reusability across different data types. File Input/Output (I/O) operations are extensively used to read and write files in binary mode, while dynamic memory allocation manages varying data sizes, especially for file name buffers. Error handling mechanisms are implemented to address potential failures in file operations, and control structures enable iterative processing of files based on their types and contents. Through the integration of these concepts, the File Metadata Analyzer achieves robustness and versatility in its metadata analysis capabilities.

## Features
Identification of file types based on magic numbers and file extensions.
Extraction of creation time, last modified time, and file size.
Analysis of file permissions.
Specialized handling for specific file types including text files (TXT) and CSV files.
## Dependencies
STB Image - For loading images.<br>
C++ Filesystem Library - For file and directory manipulation.

## Installation
Clone the repository:
```bash
git clone https://github.com/HemanthsReddy/FileMetaDataAnalyzer
```

## Compile the program using a C++ compiler (e.g., g++):
```bash
g++ --std=c++20 main.cpp -o file_metadata_analyzer
```
<font color="red">Note: Ensure that your compiler supports the C++20 standard. If you encounter any issues, you may need to update your compiler or use a different one that supports C++20.</font>

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
