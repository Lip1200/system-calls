#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>

// Function to convert mode_t type to char
char fileType(mode_t type) {
    char fileType;
    switch (type & S_IFMT) {
        case S_IFDIR:
            fileType = 'd';
            break;
        case S_IFREG:
            fileType = '-';
            break;
        case S_IFLNK:
            fileType = 'l';
            break;
        default:
            fileType = '?'; // Other file type
            break;
    }
    return fileType;
}

// Function that converts file permissions to string format (rwx).
char* modeToRwx(mode_t mode) {
    char* rwx = malloc(10 * sizeof(char)); // 9 characters for rwx and 1 for null terminator '\\0'
    if (rwx == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    // Owner
    rwx[0] = (mode & S_IRUSR) ? 'r' : '-';
    rwx[1] = (mode & S_IWUSR) ? 'w' : '-';
    rwx[2] = (mode & S_IXUSR) ? 'x' : '-';

    // Group
    rwx[3] = (mode & S_IRGRP) ? 'r' : '-';
    rwx[4] = (mode & S_IWGRP) ? 'w' : '-';
    rwx[5] = (mode & S_IXGRP) ? 'x' : '-';

    // Other users
    rwx[6] = (mode & S_IROTH) ? 'r' : '-';
    rwx[7] = (mode & S_IWOTH) ? 'w' : '-';
    rwx[8] = (mode & S_IXOTH) ? 'x' : '-';

    rwx[9] = '\\0'; // Add null terminator at the end

    return rwx;
}

// Function that lists files in a directory specified by dirPath.
void listFiles(const char* dirPath) {
    // Open the specified directory
    DIR* dir= opendir(dirPath);
    struct dirent* entry;
    struct stat fileInfos;

    // Check if directory is opened correctly
    if (dir == NULL) {
        perror("Error opening folder");
        exit(EXIT_FAILURE);
    }

    // Traverse each entry in the directory
    while ((entry = readdir(dir)) != NULL) {

        // Ignore "." and ".." entries
        if (strncmp(entry->d_name, ".", 1) != 0 && strncmp(entry->d_name, "..", 2) != 0) { // add \\0 and increase by 1 to include hidden files
            // Build full file/folder path with malloc
            char* filePath = malloc(strlen(dirPath) + strlen(entry->d_name) + 2);
            if (filePath == NULL) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
            // Write output to string
            sprintf(filePath, "%s/%s", dirPath, entry->d_name);

            // Get file/folder information
            if (lstat(filePath, &fileInfos) < 0) {
                perror("Error retrieving file information");
                exit(EXIT_FAILURE);
            }
            // Date formatting for strftime function
            int max_size = 80;
            char dateModif[max_size];
            struct tm* mtime = localtime(&fileInfos.st_mtime);
            if (strftime(dateModif, max_size, "%a %b %d %H:%M:%S %Y", mtime) == 0) {
                fprintf(stderr, "Date formatting error strftime()");
                exit(EXIT_FAILURE);
            }
            // Display file/folder details
            char* rwxMode = modeToRwx(fileInfos.st_mode);
            printf("%c %-10s %10ld %-10s %s \\n",
                   fileType(fileInfos.st_mode), rwxMode, fileInfos.st_size, dateModif, filePath);
            free(rwxMode);  // Free allocated memory from modeToRwx
            if (S_ISDIR(fileInfos.st_mode))
                listFiles(filePath); // If folder -> recursive call -> explore subfolder

            free(filePath); // Free malloc

        }
    }
    // Close directory
    closedir(dir);
}

// Function to populate stat structure based on isF (links copied as links) or not (dereferenced).
int statInfo(char* path, struct stat* pathInfos, int isF){
    if (access(path, F_OK) == 0){  // File at path exists
        if(isF){ // Links copied as links
            if (lstat(path, pathInfos) < 0) { // Populate stat struct
                perror("Error retrieving file information");
                return -1;
            }
        }else{ // Links are dereferenced
            if (stat(path, pathInfos) < 0) {
                perror("Error retrieving file information");
                return -1;
            }
        }
    }else return -1;
    return 0;
}