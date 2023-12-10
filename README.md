# Project Overview

This repository contains various projects, each with its own functionality and focus. Below is an explanation of each directory and its contents.

## Directory Structure

### 1. **Hash**

This project provides a hashing program that computes the hash of files or strings using different algorithms.

- `Makefile`: Script to compile the program.
- `hash.c`, `hash.h`: Core logic for hashing.
- `option.c`, `option.h`: Handles command-line options.
- `main.c`: Entry point of the program.
- `test.txt`, `test2.txt`: Example test files.

### 2. **Locker**

A file-locking system that manages file access with locks.

- `Makefile`: Compiles the program.
- `func.c`, `func.h`: Utility functions for file management.
- `main.c`: Coordinates the locking functionality.
- `RapportTP3.md`: Project report.
- `readMe.md`: Project documentation.

### 3. **Ultra-cp**

A custom file-copying utility that allows copying files and directories with various options.

- `Makefile`: Script for compiling.
- `copy.c`, `copy.h`: Implements copying functionality.
- `func.c`, `func.h`: Helper functions.
- `option.c`, `option.h`: Command-line parsing for options.
- `main.c`: Entry point.
- `README.md`: Documentation.
- `Rapport.md`: Detailed project report.

### 4. **client_serveur**

Implements a client-server architecture where clients connect to the server to guess a number.

- `Makefile`: Script to compile both client and server.
- `client.c`: Client program.
- `serveur.c`: Server program.
- `common.h`: Shared definitions.
- `fonctions.c`, `fonctions.h`: Common functions for both client and server.
- `README.md`: Project documentation.
- `Rapport.md`: Detailed project report.

### 5. **pizzeria**

Simulates a pizzeria where pizzas are made and served by separate processes (cook and server).

- `Makefile`: Script to compile the pizzeria simulation.
- `cook.c`: The cook process that prepares pizzas.
- `server.c`: The server process that serves pizzas.
- `pizza_rack.h`: Defines the shared memory structure (pizza rack).
- `rapport.md`: Project report.
- `README.md`: Documentation.

### 6. **wish**

A custom shell project offering basic UNIX-like functionality, such as executing commands and job control.

- `Makefile`: Compiles the shell.
- `func.c`, `func.h`: Implements utility functions for shell commands.
- `main.c`: Main program for the shell.
- `man.pdf`: Manual for the shell.
- `readMe.md`: Project documentation.

## License

This repository is licensed under the MIT License.
