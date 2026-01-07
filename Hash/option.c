#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <openssl/evp.h>

// Function to parse command line options
int parseOptions(int argc, char* argv[], int* isFile, int* indFile, int* isT, int* indT)
{
    int opt;

    // Use getopt to process command line options
    while ((opt = getopt(argc, argv, "t:f")) != -1)
    {
        switch (opt)
        {
        case 'f':
            // -f option is specified, indicating the program should process a file
            *isFile = 1;
            // Store the index of the first file argument
            *indFile = optind-1;
            break;
        case 't':
            // -t option is specified, indicating the hash algorithm
            *isT = 1;
            // Store the index of the hash algorithm
            *indT = optind-1;
            // Check if an argument is specified with -t option
            if (optarg == NULL)
            {
                printf("Unknown message digest %s\\n", optarg);
                return -1;
            }
            break;
        default: /* '?' */
            // An unrecognized option is specified
            fprintf(stderr, "Usage: %s [-t type] [-f file] name\\n",
                    argv[0]);
            return -1;
        }
    }

    return 0;
}
