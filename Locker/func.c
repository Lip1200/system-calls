#include <stdio.h>
#include "func.h"
#include <fcntl.h>


void printHelp(void){
    puts("*-----------------------------------------------------------------------*");
    puts("|  Format: cmd type start length [whence]                               |");
    puts("|  cmd:    ’g’ (F_GETLK), ’s’ (F_SETLK), ’w’ (F_SETLKW)                 |");
    puts("|  type:   'r' (F_RDLCK), 'w' (F_WRLCK) or 'u' (F_UNLCK)                |");
    puts("|  start:  Lock start \"offset\"                                         |");
    puts("|  length: number of bytes to lock                                      |");
    puts("|  whence: 's' (SEEK_SET, default), 'c' (SEEK_CUR) or 'e'(SEEK_END)     |");
    puts("*-----------------------------------------------------------------------*");
}

int parseComm(struct Commandes* comm, int* cmdLock, struct flock* fl) {
    fl->l_start = comm->start;
    fl->l_len = comm->length;
    // Switch on command type
    switch (comm->cmd) {
        case 'g':
            *cmdLock = F_GETLK;
            break;
        case 's':
            *cmdLock = F_SETLK;
            break;
        case 'w':
            *cmdLock = F_SETLKW;
            break;
        default:
            printf("Invalid argument '%c' for cmd\n", comm->cmd);
            return -1;
    }

    // Switch on lock type
    switch (comm->l_type) {
        case 'r':
            fl->l_type = F_RDLCK;
            break;
        case 'w':
            fl->l_type = F_WRLCK;
            break;
        case 'u':
            fl->l_type = F_UNLCK;
            break;
        default:
            printf("Invalid argument '%c' for l_type\n", comm->l_type);
            return -1;
    }

    // Switch on whence parameter
    switch (comm->whence) {
        case 's':
            fl->l_whence = SEEK_SET;
            break;
        case 'c':
            fl->l_whence = SEEK_CUR;
            break;
        case 'e':
            fl->l_whence = SEEK_END;
            break;
        default:
            printf("Invalid argument '%c' for whence\n", comm->whence);
            return -1;
    }
    return 0;
}

void lockInfos(int pid, int commande, struct flock* fl) {

    switch (commande) {
        case F_GETLK:
            // If user wants to know if they can set a lock or not
            switch (fl->l_type) {
                case F_UNLCK:
                    printf("The file has no limiting lock\n");
                    break;
                case F_RDLCK:
                    printf("There is a \"READ lock\" starting at %lld with size %lld\nOwner process > PID=%d", fl->l_start, fl->l_len, fl->l_pid);
                    break;
                case F_WRLCK:
                    printf("There is a \"WRITE lock\" starting at %lld with size %lld\nOwner process > PID=%d", fl->l_start, fl->l_len, fl->l_pid);
                    break;
            }
            break;

        case F_SETLK:
            // If user wants to set a lock immediately
            switch (fl->l_type) {
                case F_UNLCK:
                    printf("[PID=%d] released a lock\n", pid);
                    break;
                case F_RDLCK:
                    printf("A \"READ lock\" was set from %lld to %lld\nLock owner process > PID=%d\n", fl->l_start, fl->l_start + fl->l_len, pid);
                    break;
                case F_WRLCK:
                    printf("A \"WRITE lock\" was set from %lld to %lld\nLock owner process > PID=%d\n", fl->l_start, fl->l_start + fl->l_len, pid);
                    break;
            }
            break;

        case F_SETLKW:
            // If user wants to set a lock as soon as possible
            switch (fl->l_type) {
                case F_UNLCK:
                    printf("[PID=%d] released a lock\n", pid);
                    break;
                case F_RDLCK:
                    printf("A \"READ lock\" was set from %lld to %lld\nLock owner process > PID=%d\n", fl->l_start, fl->l_start + fl->l_len, pid);
                    break;
                case F_WRLCK:
                    printf("A \"WRITE lock\" was set from %lld to %lld\nLock owner process > PID=%d\n", fl->l_start, fl->l_start + fl->l_len, pid);
                    break;
            }
            break;
    }
}