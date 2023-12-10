# Pizzeria Management Simulation

## Description

This project simulates a pizzeria where pizzas are prepared, stored, and served. The system consists of two main processes: a cook (`cook.c`) who prepares pizzas and places them on a rack, and a server (`server.c`) who serves the pizzas from the rack. Synchronization between these processes is managed through semaphores and shared memory.

## Project Structure

- **`cook.c`**: The cook process, responsible for preparing pizzas and placing them on the pizza rack.
- **`server.c`**: The server process, responsible for serving pizzas from the pizza rack.
- **`pizza_rack.h`**: Defines the structure for the pizza rack and includes necessary libraries for shared memory and semaphores.
- **`Makefile`**: Used to compile the program.
- **`rapport.md`**: Documentation of the project's design and objectives.

## Features

- **Inter-process Communication (IPC)**: The cook and server processes communicate through shared memory.
- **Semaphore-Based Synchronization**: Semaphores are used to manage the pizza rack's available space and the availability of pizzas.
- **Error Handling**: Both processes manage errors related to shared memory and semaphore operations.
- **Resource Cleanup**: After execution, semaphores and shared memory are cleaned up to avoid memory leaks.

## Compilation

To compile the project:

```bash
make
```

## Execution

1. Start the cook process to begin preparing pizzas:
   ```bash
   ./cook
   ```
2. Start the server process to begin serving pizzas:
   ```bash
   ./server
   ```

Both processes will communicate through shared memory to simulate the pizzeria's workflow.

## Synchronization and Communication

- **Shared Memory**: Used to represent the pizza rack (`P_rack`).
- **Semaphores**: Coordinate the availability of pizzas and the space on the rack.

## Cleaning Up

To remove compiled files:

```bash
make clean
```

## License

This project is licensed under the MIT License.
