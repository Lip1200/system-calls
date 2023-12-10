#include <stdio.h>
#include "func.h"
#include <fcntl.h>


void printHelp(void){
    puts("*-----------------------------------------------------------------------*");
    puts("|  Format: cmd type start length [whence]                               |");
    puts("|  cmd:    ’g’ (F_GETLK), ’s’ (F_SETLK), ’w’ (F_SETLKW)                 |");
    puts("|  type:   ’r’ (F_RDLCK), ’w’ (F_WRLCK) ou ’u’ (F_UNLCK)                |");
    puts("|  start:  Début du vérrou \"offset\"                                     |");
    puts("|  length: nombres d'octets à vérrouiller                               |");
    puts("|  whence: ’s’ (SEEK_SET, default), ’c’ (SEEK_CUR) ou ’e’(SEEK_END)     |");
    puts("*-----------------------------------------------------------------------*");
}

int parseComm(struct Commandes* comm, int* cmdLock, struct flock* fl) {
    fl->l_start = comm->start;
    fl->l_len = comm->length;
    // Switch sur le type de commande
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

    // Switch sur le type de verrou
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

    // Switch sur le paramètre whence
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
            // Si l'utilisateur souhaite savoir s'il peut poser un verrou ou non
            switch (fl->l_type) {
                case F_UNLCK:
                    printf("Le fichier n'a pas de verrou limitant\n");
                    break;
                case F_RDLCK:
                    printf("Il y a un verrou \"READ lock\" commençant à %lld de taille %lld\nProcessus propriétaire > PID=%d", fl->l_start, fl->l_len, fl->l_pid);
                    break;
                case F_WRLCK:
                    printf("Il y a un verrou \"WRITE lock\" commençant à %lld de taille %lld\nProcessus propriétaire > PID=%d", fl->l_start, fl->l_len, fl->l_pid);
                    break;
            }
            break;

        case F_SETLK:
            // Si l'utilisateur souhaite poser un verrou dans l'immédiat
            switch (fl->l_type) {
                case F_UNLCK:
                    printf("[PID=%d] a fait sauter un verrou\n", pid);
                    break;
                case F_RDLCK:
                    printf("Un verrou \"READ lock\" a été posé de %lld à %lld\nProcessus propriétaire du verrou > PID=%d\n", fl->l_start, fl->l_start + fl->l_len, pid);
                    break;
                case F_WRLCK:
                    printf("Un verrou \"WRITE lock\" a été posé de %lld à %lld\nProcessus propriétaire du verrou > PID=%d\n", fl->l_start, fl->l_start + fl->l_len, pid);
                    break;
            }
            break;

        case F_SETLKW:
            // Si l'utilisateur souhaite poser un verrou dès qu'il sera possible d'en poser un
            switch (fl->l_type) {
                case F_UNLCK:
                    printf("[PID=%d] a fait sauter un verrou\n", pid);
                    break;
                case F_RDLCK:
                    printf("Un verrou \"READ lock\" a été posé de %lld à %lld\nProcessus propriétaire du verrou > PID=%d\n", fl->l_start, fl->l_start + fl->l_len, pid);
                    break;
                case F_WRLCK:
                    printf("Un verrou \"WRITE lock\" a été posé de %lld à %lld\nProcessus propriétaire du verrou > PID=%d\n", fl->l_start, fl->l_start + fl->l_len, pid);
                    break;
            }
            break;
    }
}