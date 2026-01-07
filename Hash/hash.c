#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <openssl/evp.h>
#include "option.h"
#include "hash.h"


void FileHash(char* file, const EVP_MD* md)
{
    // Initialize the hash context
    EVP_MD_CTX* mdctx;
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL)
    {
        fprintf(stderr, "Error initializing hash context.\\n");
    }

    // Initialization
    if (!EVP_DigestInit_ex(mdctx, md, NULL))
    {
        printf("Initialization error.\\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }
    // Open file in read mode
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Unable to open file: %s\n", file);
        EVP_MD_CTX_free(mdctx);
        return;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    // Read file line by line and update hash
    while ((read = getline(&line, &len, fp)) != -1)
    {

        if (!EVP_DigestUpdate(mdctx, line, read))
        {
            printf("Message digest update error.\\n");
            EVP_MD_CTX_free(mdctx);
            exit(1);
        }
    }

    // Finalize hash and get result
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    if (!EVP_DigestFinal_ex(mdctx, hash, &hash_len))
    {
        printf("Message digest finalization failed.\\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    // Display computed hash
    printf("Hash (%s): ", EVP_MD_name(md));
    for (unsigned int i = 0; i < hash_len; ++i)
    {
        printf("%02x", hash[i]);
    }
    printf("\\n");

    // Free memory and close file
    EVP_MD_CTX_free(mdctx);
    fclose(fp);
    if (line)
    {
        free(line);
    }
}

void StringHash(char* input, const EVP_MD* md, int size_input)
{
    // Initialize the hash context
    EVP_MD_CTX *mdctx;
    mdctx = EVP_MD_CTX_new();

    if (!EVP_DigestInit_ex(mdctx, md, NULL))
    {
        printf("Initialization error.\\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the resulting string
    unsigned char *data = (unsigned char *)malloc(size_input);

    // Traverse input string and copy characters with spaces
    int data_index = 0;
    for (int i = 0; i < size_input; ++i)
    {
        data[data_index] = input[i];
        data_index++;
    }

    // Update hash with data
    if (!EVP_DigestUpdate(mdctx, data, size_input))
    {
        printf("Message digest update failed.\\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    // Finalize hash and get result
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    if (!EVP_DigestFinal_ex(mdctx, hash, &hash_len))
    {
        printf("Message digest finalization failed.\\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    // Display computed hash
    printf("Hash (%s): ", EVP_MD_name(md));
    for (unsigned int i = 0; i < hash_len; ++i)
    {
        printf("%02x", hash[i]);
    }
    printf("\\n");

    // Free dynamically allocated memory
    EVP_MD_CTX_free(mdctx);
    free(data);
}