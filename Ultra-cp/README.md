# Ultra-cp File Copy Program

## Description

Ultra-cp is a file copying program designed to handle a wide variety of file types, including regular files, symbolic links, and directories. The program is modular, allowing for advanced file manipulation options and command-line parsing.

## Project Structure

1. **copy.c & copy.h**: Implements the core logic for file and directory copying, including advanced copy options.
2. **func.c & func.h**: Provides utility functions for file management, such as listing files in a directory.
3. **option.c & option.h**: Parses command-line options given by the user.
4. **main.c**: Coordinates the overall operations, calling the necessary modules based on user input.

## Compilation

To compile the program, use the following command in the project directory:

```bash
make all
```

This will compile all the necessary source files and link them to create the executable.

## Usage

The program can be run with several command-line options to copy files or directories. The basic usage is as follows:

```bash
./ultra-cp [options] source destination
```

### Options:

- `-r`: Recursively copy directories.
- `-l`: Preserve symbolic links.
- `-v`: Enable verbose mode to display progress.

## Example

To copy a file or directory:

```bash
./ultra-cp -r /source/path /destination/path
```

## Troubleshooting

If any issues occur during the copy, ensure that the source files are accessible and that you have the necessary permissions for the destination directory.

## License

This project is licensed under the MIT License.
