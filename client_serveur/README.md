# Network-Based Guessing Game (TP4)

## Description

This project implements a simple network-based guessing game using TCP sockets. Players (clients) connect to a server and attempt to guess a randomly generated number by the server. Each client plays independently, with real-time feedback from the server.

## Compilation

To compile both the server and client programs, follow these steps:

1. Open a terminal.
2. Navigate to the project directory.
3. Run the following command:
   ```bash
   make
   ```
   This will generate two executables: `serveur` (server) and `client`.

## Execution

### Server

To start the server:

```bash
./serveur <port>
```

Replace `<port>` with the desired port number.

### Client

To connect a client to the server:

```bash
./client <server_ip> <port>
```

Replace `<server_ip>` with the server's IP address and `<port>` with the port number the server is using.

## Features

- **Multi-client Support**: The server can handle multiple client connections simultaneously.
- **Independent Gameplay**: Each client plays the guessing game independently.
- **Hint System**: Clients receive hints if their guess is too high or too low.
- **TCP-based Communication**: Uses TCP sockets for reliable communication between server and client.

## Configuration

- **Default Port**: The server port must be specified during execution.
- **Max Attempts**: Defined in `common.h` and can be adjusted as needed.

## File Overview

### `client.c`

- Establishes a TCP connection to the server.
- Handles user input and communicates guesses to the server.
- Receives feedback on guesses from the server.

### `serveur.c`

- Waits for incoming client connections.
- Manages each client independently using `fork()` to create separate processes.
- Provides feedback on client guesses and handles game logic.

### `common.h`

- Contains shared constants and definitions used by both the client and server.
- Defines the structure for socket communication and game parameters.

### `fonctions.c` and `fonctions.h`

- Implements utility functions such as random number generation and guess validation.
- Handles sending responses between the client and server.

## Example Usage

1. Start the server:

   ```bash
   ./serveur 8080
   ```

2. Connect a client:

   ```bash
   ./client 127.0.0.1 8080
   ```

3. The client will receive instructions and can start guessing numbers.

## Cleaning Up

To remove the compiled executables and object files:

```bash
make clean
```

## License

This project is licensed under the MIT License.
