def files_to_binary_dump(files, output_file):
    with open(output_file, 'wb') as binary_file:
        for file_name in files:
            with open(file_name, 'rb') as f:
                content = f.read()
                binary_file.write(content)

files_to_convert = ["FMA/Image.jpeg", "FMA/Image.jpeg"]  # Update with your JPEG file names
binary_dump_file = "binary_dump.bin"  # Output binary dump file

files_to_binary_dump(files_to_convert, binary_dump_file)
print(f"Binary dump file '{binary_dump_file}' has been created.")
