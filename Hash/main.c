#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/evp.h>
#include "hash.h"
#include "option.h"
#include <string.h>


int main(int argc, char *argv[])
{
    int isFile = 0;     // Indicates if -f option is specified
    int indFile = -1;   // Stores the index of the first file argument
    int isT = 0;        // Indicates if -t option is specified
    int indT = -1;      // Stores the index of the hash algorithm
    int start;          // Determines from which argv index to start processing
                        // the input string when -f option is not specified

    // Check command line options
    if(parseOptions(argc, argv, &isFile, &indFile, &isT, &indT) == -1){
        fprintf(stderr, "Usage: %s [-t type] [-f file] name\\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    // If -t option is not selected, default to SHA-1
    const EVP_MD* md;
    if (indT == -1)
        md = EVP_get_digestbyname("sha1");
    else
        md = EVP_get_digestbyname(argv[indT]);
    
    if (md == NULL) {
        fprintf(stderr, "Unknown message digest algorithm\n");
        exit(EXIT_FAILURE);
    }
    
    if (isFile)  // If -f is selected, pass all files given as arguments to hash function
    {
        // Hash the list of files passed as arguments
        for (int i = indFile+1; i < argc; i++){
            printf("File %s\\n", argv[i]);
            FileHash(argv[i], md); 
        }
    }
    else
    {
        if(isT) // Check if -t option is selected and set hash type accordingly
            start = indT+1;
        else
            start = 1;

        // Calculate input size to hash
        int size_input = strlen(argv[start]);
        StringHash(argv[start], md, size_input);
    }

    exit(EXIT_SUCCESS);
}