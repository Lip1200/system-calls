#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "func.h"


int main (int argc, char* argv[]){
    // The program takes a single file as input
    if (argc != 2){
        printf("Usage %s : [file]", argv[0]);
        return -1;
    }
    int fd = open(argv[1], O_RDWR);
    if ( fd < 0){
        perror("Unable to open file");
        return -1;
    }

    int running = 1;
    while(running){
        int pid = getpid();
        // Declare structure to hold commands
        struct Commandes comm;
        // Initialize whence to 's' --> SEEK_SET
        comm.whence = 's';

        int cmdLock;
        struct flock fl;
        memset(&fl, 0, sizeof(fl));
        char input[100] ; // buffer

        // Display pid > for user prompt
        printf("\nType '?' for help and 'q' to quit the program.\nPID = %d > ", pid);

        // Read input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Count number of arguments and fill the Commandes structure
        int count = sscanf(input, "%c %c %d %d %c", &comm.cmd, &comm.l_type, &comm.start, &comm.length, &comm.whence);

        if(count == 1){
            if(strcmp(input, "q\n") == 0){
                running = 0;
                break;
            }else{
                printHelp();
            }
        }else if ((count < 4) || (count > 5)){
            printf("Argument error\\n");
            printHelp();
        }else if ((count == 4) || (count == 5)){
            parseComm(&comm, &cmdLock, &fl);
            // Call fcntl to set the lock
            int status = fcntl(fd, cmdLock, &fl) ;
            if (status < 0){
                // Check if there is a conflicting lock
                struct flock temp_fl = fl; // Copy of flock structure for verification
                if (fcntl(fd, F_GETLK, &temp_fl) == -1) {
                    perror("fcntl F_GETLK error");
                    return -1;
                }
                // If lock is not available
                if (temp_fl.l_type != F_UNLCK) {
                    if(temp_fl.l_type == F_RDLCK){
                        printf("There is a \\"READ lock\\" starting at %lld with size %lld\\nOwner process > PID=%d\\n", temp_fl.l_start, temp_fl.l_len, temp_fl.l_pid);
                    }
                    if(temp_fl.l_type == F_WRLCK){
                        printf("There is a \\"WRITE lock\\" starting at %lld with size %lld\\nOwner process > PID=%d\\n", temp_fl.l_start, temp_fl.l_len, temp_fl.l_pid);
                    }
                    continue;
                }
            }else{
                // Call lock function to display result
                lockInfos(pid, cmdLock, &fl);
            }
        }else{
            printf("Erroneous request!\\n");
            printHelp();
        }
    }
    close(fd);
    return 0;
}