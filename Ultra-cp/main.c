#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "option.h"
#include "copy.h"
#include "func.h"


int main(int argc, char *argv[]) {

    int isA = 0; // Flag to check if -a option is selected --> modifies file/folder permissions
    int isF = 0; // Flag to check if -f option is selected --> links copied as links
    int nbOpt = 0; // Counter to get number of selected options

    // Check command line options
    if (parseOptions(argc, argv, &isA, &isF, &nbOpt) == -1) {
        fprintf(stderr, "Usage: %s [-a] [-f] source(s) destination\\n", argv[0]);
        return -1;
    }

    // Listing if not enough arguments
    if ((argc - nbOpt) < 3){
        if((argc - nbOpt) == 2){
            listFiles(argv[nbOpt+1]); // Listing from directory argument
        }else if ((argc - nbOpt) < 2) 
        {
            listFiles("."); // Listing from current directory if no arguments
        }else{
            // Show correct usage after listing files and exit
            fprintf(stderr, "Usage: %s source(s) destination\\n", argv[0]);
            return -1;
        }
    }else{    // If two or more arguments

        // Pointer to last argument which is the destination
        char *destination = argv[argc - 1];
        // Get destination info
        struct stat destInfos;
        // Check destination directory existence
        if (access(destination, F_OK) != 0) {
            // Create directory with desired permissions
            // For example, 0755 allows owner to read, write and execute,
            // while others can only read and execute.
            if (mkdir(destination, 0755) != 0) {
                perror("Error creating destination directory");
                return -1;
            }
        }
        if (statInfo(destination, &destInfos, isF) < 0) {
            fprintf(stderr, "Error calling statInfo function on destination\\n");
            return -1;
        }
        for (int i = nbOpt + 1; i < argc - 1; i++) {
            struct stat sourceInfos;
            if (statInfo(argv[i],&sourceInfos, isF)< 0) {
                fprintf(stderr, "Error calling statInfo function on source %s\\n", argv[i]);
                return -1;
            }
            // Case where file or source (reg || link) and destination is reg
            if (((S_ISLNK(sourceInfos.st_mode)||(S_ISREG(sourceInfos.st_mode))) && (S_ISREG(destInfos.st_mode)))) {
                // Check if source size differs from destination size
                // or if source modification date is later than destination's
                if ((sourceInfos.st_size != destInfos.st_size) || (sourceInfos.st_mtime > destInfos.st_mtime)) {
                    // Replace destination file with source file
                    copyFile(argv[i], destination, isA);
                } else {
                    // Do nothing, destination file is newer or same size as source
                    printf("%s: newer or same size as source file. No action needed.\\n", destination);
                }
            }else if (S_ISDIR(sourceInfos.st_mode) && S_ISDIR(destInfos.st_mode)){
                // Call function to copy file/folder
                ultraCP(argv[i], destination, isA, isF);

            }else return -1;
        }
    }
    return 0;
}

