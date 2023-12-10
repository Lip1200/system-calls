# TP1_Hash Program

This program computes the hash of a file or string using various hashing algorithms. It utilizes the OpenSSL library for hash calculations.

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Compilation](#compilation)
3. [Usage](#usage)
4. [Examples](#examples)
5. [Troubleshooting](#troubleshooting)
6. [Warnings](#warnings)

## Prerequisites

Ensure that OpenSSL is installed on your system. If not, you can download and install it from the official OpenSSL website: [https://www.openssl.org/](https://www.openssl.org/).

## Compilation

To compile the program, use the following command in the project directory:

```bash
make all
```

This command compiles the main source file (`main.c`) and the associated implementation files (`hash.c` and `option.c`) while linking the OpenSSL libraries (`-lssl -lcrypto`).

## Usage

The program supports two main options:

- `-f`: Specify one or more files to hash.
- `-t`: Specify the hashing algorithm to use.

Usage examples:

```bash
./hash -f file1 file2 ...
```

or

```bash
./hash -t algorithm -f file.txt
```

or

```bash
./hash -t algorithm "String to hash"
```

## Examples

- To hash the contents of `test.txt` using the SHA-256 algorithm:

```bash
./hash -t sha256 -f test.txt
```

- To hash the string "Hello, World!" using the MD5 algorithm:

```bash
./hash -t md5 "Hello, World!"
```

## Troubleshooting

If you get unexpected hash results, ensure that the file or string content doesn't contain invisible characters or encoding differences. Some text editors may add line breaks or encoding formats that affect the hash.

Make sure to use the appropriate options in your text editor to ensure correct file or string formatting.
