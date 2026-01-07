#ifndef COPY_H
#define COPY_H

/**
 * Copies the specified file from source to destination.
 * @param sourcePath The source file path.
 * @param destinationPath The destination file path.
 * @param isA Flag to check if -a option is enabled.
 */
void copyFile(char* sourcePath, char* destinationPath, int isA);

/**
 * Copies the specified file or folder from source to destination.
 * @param sourcePath The source file or folder path.
 * @param destinationPath The destination file or folder path.
 * @param isA Flag to check if -a option is enabled.
 * @param isF Flag to check if -f option is enabled.
 */
void ultraCP(char* sourcePath, char* destinationPath, int isA, int isF);

#endif //COPY_H
