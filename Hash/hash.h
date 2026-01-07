#ifndef HASH_H
#define HASH_H

#include <openssl/evp.h>

/**
 * @brief Computes the hash of a specified file.
 * 
 * This function takes a file path as input, computes its hash using
 * the hash algorithm specified by the digest pointer, and displays the hash result.
 * 
 * @param file Path of the file to hash.
 * @param digest Pointer to the hash algorithm to use.
 */
void FileHash(char* file, const EVP_MD* digest);

/**
 * @brief Computes the hash of a specified string.
 * 
 * This function takes a string as input, computes its hash using
 * the hash algorithm specified by the digest pointer, and displays the hash result.
 * 
 * @param input String to hash.
 * @param digest Pointer to the hash algorithm to use.
 * @param size_input Size of the string to hash.
 */
void StringHash(char* input, const EVP_MD* digest, int size_input);

#endif /* HASH_H */
