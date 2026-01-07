#include "option.h"
#include <stdio.h>
#include <getopt.h>

int parseOptions(int argc, char* argv[], int* isA, int* isF, int* nbOpt){
    int opt; // Variable to store currently parsed option
    // Loop to parse all provided options
    while ((opt = getopt(argc, argv, "af")) != -1){
        switch (opt) {
            case 'a':
                *isA = 1;
                *nbOpt +=1;
                break;
            case 'f': // Option to specify links will be copied as links
                *isF = 1;
                *nbOpt +=1;
                break;
            default: // Handle unrecognized options or errors
                fprintf(stderr, "Usage: %s [-a] [-f] source(s) destination\\n", argv[0]);
                return -1; // Return error for unrecognized options
        }
    }
    return 0;
}

