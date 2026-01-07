#ifndef OPTIONS_H
#define OPTIONS_H
#include <openssl/evp.h>

/**
 * @brief Parses command line options and sets corresponding flags and indices.
 * 
 * This function parses the command line options provided by the user and sets
 * the corresponding flags and indices based on the options. The function supports
 * the following options:
 * 
 * - `-f`: Sets the isFile flag to 1 and stores the index in indFile.
 * - `-t`: Sets the isT flag to 1 and stores the index in indT. Additionally, checks and stores
 * the specified hash type.
 * 
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @param isFile Pointer to an integer flag for the file option.
 * @param indFile Pointer to an integer variable to store the file option index.
 * @param isT Pointer to an integer flag for the hash type option.
 * @param indT Pointer to an integer variable to store the hash type option index.
 * 
 * @return 0 if parsing is successful, -1 if there is an error in the options.
 * 
 * @warning This function modifies the values pointed to by isFile, indFile, isT and indT.
 */
int parseOptions(int argc, char* argv[], int* isFile, int* indFile, int* isT, int* indT);

#endif /* OPTIONS_H */
