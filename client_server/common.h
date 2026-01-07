#ifndef COMMON_H
#define COMMON_H

// Standard includes for input/output operations, memory management, etc.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Includes for network and socket operations
#include <sys/socket.h>
#include <arpa/inet.h>

// Includes for various system operations
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Definition of upper bound for guessing game
#define MAX_GUESS 20

// Maximum number of attempts allowed for guessing game
#define MAX_TENTATIVES 4

// Codes to indicate player's guess status
#define TOO_LOW -1
#define WIN 0
#define TOO_HIGH 1
#define LOSE 2

// Buffer size for socket read/write operations
#define BUFFER_SIZE 256

#endif // COMMON_H
