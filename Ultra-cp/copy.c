#include "copy.h"
#include "statInfo.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include <libgen.h>


void copyFile(char* sourcePath, char* destinationPath, int isA) {
    int fd_source, fd_destination;
    char buf[4096];
    ssize_t bytesRead;
    struct stat sourceInfos;

    // Open source file
    if ((fd_source = open(sourcePath, O_RDONLY)) < 0) {
        fprintf(stderr, "Error opening source %s: %s\\n", sourcePath, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Get file information
    if (fstat(fd_source, &sourceInfos) < 0) {
        perror("Error retrieving file information");
        exit(EXIT_FAILURE);
    }
    // Open destination file and create if it doesn't exist with same permissions as source
    if ((fd_destination = open(destinationPath, O_WRONLY | O_CREAT, sourceInfos.st_mode)) < 0){
        perror("Error opening destinationPath");
        close(fd_source);
        exit(EXIT_FAILURE);
    }

    // Copy source file content to destination file
    while ((bytesRead = read(fd_source, buf, sizeof(buf))) > 0) {
        if ( write(fd_destination, buf, bytesRead) != bytesRead) {
            perror("Error writing to destination file");
            close(fd_source);
            close(fd_destination);
            exit(EXIT_FAILURE);
        }
    }
    if (bytesRead == -1) {
        perror("Error reading source file");
    }
    // Close file descriptors
    close(fd_source);
    close(fd_destination);
    // Modify destination file permissions if -a option is enabled
    if (isA) {
        if (chmod(destinationPath, sourceInfos.st_mode) < 0) {
            perror("Error modifying destination file permissions");
            exit(EXIT_FAILURE);
        }
    }
}

void ultraCP(char* sourcePath, char* destinationPath, int isA, int isF) {
    
    struct stat sourceInfo;
    if (statInfo(sourcePath, &sourceInfo, isF) < 0){
        fprintf(stderr, "Error calling statInfo function\\n");
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(sourceInfo.st_mode)) { // Directory
        // Open source folder
        DIR* dir = opendir(sourcePath);
        if (dir == NULL) {
            perror("Error opening source folder");
            exit(EXIT_FAILURE);
        }

        // Dynamically allocate memory for full destination path
        char* newDest = malloc(strlen(destinationPath) + strlen(basename(sourcePath)) + 2);
        if (newDest == NULL) {
            perror("Memory allocation error");
            free(newDest);
            exit(EXIT_FAILURE);
        }
        sprintf(newDest, "%s/%s", destinationPath, basename(sourcePath));

        // Create source folder in destination
        mkdir(newDest, sourceInfo.st_mode);


        // Traverse each entry in source folder
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            // Ignore "." and ".." entries
            if (strncmp(entry->d_name, ".\\0", 2) != 0 && strncmp(entry->d_name, "..\\0", 3) != 0) {
                
                // Dynamically allocate memory for full source path
                char* newSource = malloc(strlen(sourcePath) + strlen(entry->d_name) + 2);
                if (newSource == NULL) {
                    perror("Memory allocation error");
                    exit(EXIT_FAILURE);
                }
                // Build full path for source
                sprintf(newSource, "%s/%s", sourcePath, entry->d_name);                

                if (statInfo(newSource, &sourceInfo, isF) < 0){
                    fprintf(stderr, "Error calling statInfo function\\n");
                    exit(EXIT_FAILURE);
                }
                if (S_ISDIR(sourceInfo.st_mode)){
                    // Recursive call to copy folder content
                    ultraCP(newSource, newDest, isA, isF);
                }
                else if(S_ISREG(sourceInfo.st_mode) || S_ISLNK(sourceInfo.st_mode)){
                    char* newDestFile = malloc(strlen(newDest) + strlen(basename(newSource)) + 2);
                    if (newDestFile == NULL) {
                        perror("Memory allocation error");
                        exit(EXIT_FAILURE);
                    }
                    sprintf(newDestFile, "%s/%s", newDest, basename(newSource));
                    copyFile(newSource, newDestFile, isA);
                    free(newDestFile);
                }
                // Free dynamically allocated memory
                free(newSource);
            }
        }
        free(newDest);
        // Modify destination file or folder permissions if -a option is enabled
        if (isA) {
            if (chmod(destinationPath, sourceInfo.st_mode) < 0) {
                perror("Error modifying destination file/folder permissions");
                exit(EXIT_FAILURE);
            }
        }
        // Close source folder
        closedir(dir);
    }
    // Function completed successfully
}