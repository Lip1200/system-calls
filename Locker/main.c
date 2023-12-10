#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "func.h"


int main (int argc, char* argv[]){
    //le programme prend un unique fichier en entrée
    if (argc != 2){
        printf("Usage %s : [fichier]", argv[0]);
        return -1;
    }
    int fd = open(argv[1], O_RDWR);
    if ( fd < 0){
        perror("Impossible d'ouvrir le fichier");
        return -1;
    }

    int exit = 1;
    while(exit){
        int pid = getpid();
        //déclare la structure pour accueillir les commandes
        struct Commandes comm;
        //initialisation de whence à 's' --> SEEK_SET
        comm.whence = 's';

        int cmdLock;
        struct flock fl;
        char input[100] ; //buffer

        //On affiche le pid > pour prompt utilisateur
        printf("\nTaper '?' pour l'aide et 'q' pour quitter le programme.\nPID = %d > ", pid);

        //vide le tampon d'entrée standard
        if (fflush(stdin) < 0){
            perror("Erreur de vidange stdin");
            return -1;
        }
        fgets(input, sizeof(input), stdin);  // Récupère une ligne de l'entrée standard (clavier)

        // on compte le nombre d'arguments et remplit la structure Commandes
        int count = sscanf(input, "%c %c %d %d %c", &comm.cmd, &comm.l_type, &comm.start, &comm.length, &comm.whence);

        if(count == 1){
            if(strcmp(input, "q\n") == 0){
                exit = 0;
                break;
            }else{
                printHelp();
            }
        }else if ((count < 4) || (count > 5)){
            printf("Erreur d'arguments\n");
            printHelp();
        }else if ((count == 4) || (count == 5)){
            parseComm(&comm, &cmdLock, &fl);
            // Appelle fcntl pour poser le verrou
            int status = fcntl(fd, cmdLock, &fl) ;
            if (status < 0){
                // Vérifie s'il y a un verrou concurrent
                struct flock temp_fl = fl; // Copie de la structure flock pour vérification
                if (fcntl(fd, F_GETLK, &temp_fl) == -1) {
                    perror("Erreur fcntl F_GETLK");
                    return -1;
                }
                // Si le verrou n'est pas disponible
                if (temp_fl.l_type != F_UNLCK) {
                    if(temp_fl.l_type == F_RDLCK){
                        printf("Il y a un verrou \"READ lock\" commençant à %lld de taille %lld\nProcessus propriétaire > PID=%d\n", temp_fl.l_start, temp_fl.l_len, temp_fl.l_pid);
                    }
                    if(temp_fl.l_type == F_WRLCK){
                        printf("Il y a un verrou \"WRITE lock\" commençant à %lld de taille %lld\nProcessus propriétaire > PID=%d\n", temp_fl.l_start, temp_fl.l_len, temp_fl.l_pid);
                    }
                    continue;
                }
            }else{
                // Appelle la fonction lock pour afficher le résultat
                lockInfos(pid, cmdLock, &fl);
            }
        }else{
            printf("Requète erronée!\n");
            printHelp();
        }
    }
    close(fd);
    return 0;
}