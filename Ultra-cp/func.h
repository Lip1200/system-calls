#ifndef FUNC_H
#define FUNC_H

#include <stdlib.h>
#include <sys/stat.h>

/**
 * @brief Lists files and folders in the specified directory.
 *
 * This function takes a directory path as input, traverses each entry
 * in the directory and displays file and folder details.
 *
 * @param dirPath Path of the directory to list.
 */
void listFiles(const char* dirPath);

/**
 * @brief Determines file type based on mode.
 *
 * This function takes a file mode as input and determines the file type
 * (directory, regular file, symbolic link, etc.).
 *
 * @param type File mode.
 * @return Character representing file type ('d' for directory, '-' for regular file, etc.).
 */
char fileType(mode_t type);

/**
 * @brief Converts file mode to rwx string.
 *
 * This function takes a file mode as input and converts permission bits
 * to a string representing read, write and execute permissions.
 *
 * @param mode File mode.
 * @return String representing read, write and execute permissions (e.g., "rwxr-xr--").
 */
char* modeToRwx(mode_t mode);

/**
 * @brief Retrieves information about a file or directory.
 *
 * This function retrieves information about the file or directory specified
 * by the given path. Information is stored in the 'struct stat'
 * pointed to by 'pathInfos'. If 'isF' is non-zero, symbolic links are
 * not dereferenced.
 *
 * @param path        The file or directory path.
 * @param pathInfos   A pointer to 'struct stat' where information will be stored.
 * @param isF         If non-zero, symbolic links are not dereferenced.
 *
 * @return            Returns 0 on success, -1 on failure (check 'errno' for details).
 */
int statInfo(char* path, struct stat* pathInfos, int isF);

#endif // FUNC_H
