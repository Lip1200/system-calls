#include "copy.h"
#include "statInfo.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include <libgen.h>


void copyFile(char* sourcePath, char* destinationPath, int isA) {
    int fd_source, fd_destination;
    char buf[4096];
    ssize_t bytesRead;
    struct stat sourceInfos;

    //ouvre le fichier source
    if ((fd_source = open(sourcePath, O_RDONLY)) < 0) {
        fprintf(stderr, "Erreur d'ouverture de la source %s: %s\n", sourcePath, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Obtient les informations sur le fichier
    if (fstat(fd_source, &sourceInfos) < 0) {
        perror("Erreur lors de la récupération des informations du fichier");
        exit(EXIT_FAILURE);
    }
    //ouvre le fichier destination et le crée s'il n'existe pas avec les meme droits que la source
    if ((fd_destination = open(destinationPath, O_WRONLY | O_CREAT, sourceInfos.st_mode)) < 0){
        perror("Erreur d'ouverture de destinationPath");
        close(fd_source);
        exit(EXIT_FAILURE);
    }

    // Copie le contenu du fichier source vers le fichier de destination
    while ((bytesRead = read(fd_source, buf, sizeof(buf))) > 0) {
        if ( write(fd_destination, buf, bytesRead) != bytesRead) {
            perror("Erreur lors de l'écriture dans le fichier de destination");
            close(fd_source);
            close(fd_destination);
            exit(EXIT_FAILURE);
        }
    }
    if (bytesRead == -1) {
        perror("Erreur lors de la lecture du fichier source");
    }
    // Ferme les descripteurs de fichiers
    close(fd_source);
    close(fd_destination);
    // Modifier les droits du fichier de destination si l'option -a est activée
    if (isA) {
        if (chmod(destinationPath, sourceInfos.st_mode) < 0) {
            perror("Erreur lors de la modification des droits du fichier de destination");
            exit(EXIT_FAILURE);
        }
    }
}

void ultraCP(char* sourcePath, char* destinationPath, int isA, int isF) {
    
    struct stat sourceInfo;
    if (statInfo(sourcePath, &sourceInfo, isF) < 0){
        fprintf(stderr, "Erreur lors de l'appel fonction statInfo\n");
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(sourceInfo.st_mode)) { // dossier
        // Ouvre le dossier source
        DIR* dir = opendir(sourcePath);
        if (dir == NULL) {
            perror("Erreur lors de l'ouverture du dossier source");
            exit(EXIT_FAILURE);
        }

        // Alloue dynamiquement de la mémoire pour le chemin complet de la destination
        char* newDest = malloc(strlen(destinationPath) + strlen(basename(sourcePath)) + 2);
        if (newDest == NULL) {
            perror("Erreur lors de l'allocation de mémoire");
            free(newDest);
            exit(EXIT_FAILURE);
        }
        sprintf(newDest, "%s/%s", destinationPath, basename(sourcePath));

        //On crée le dossier source dans la destination
        mkdir(newDest, sourceInfo.st_mode);


        // Parcourt chaque entrée dans le dossier source
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            // Ignore les entrées "." et ".."
            if (strncmp(entry->d_name, ".\0", 2) != 0 && strncmp(entry->d_name, "..\0", 3) != 0) {
                
                // Alloue dynamiquement de la mémoire pour le chemin complet de la source
                char* newSource = malloc(strlen(sourcePath) + strlen(entry->d_name) + 2);
                if (newSource == NULL) {
                    perror("Erreur lors de l'allocation de mémoire");
                    exit(EXIT_FAILURE);
                }
                // Construit le chemin complet pour la source
                sprintf(newSource, "%s/%s", sourcePath, entry->d_name);                

                if (statInfo(newSource, &sourceInfo, isF) < 0){
                    fprintf(stderr, "Erreur lors de l'appel fonction statInfo\n");
                    exit(EXIT_FAILURE);
                }
                if (S_ISDIR(sourceInfo.st_mode)){
                    // Appel récursif pour copier le contenu du dossier
                    ultraCP(newSource, newDest, isA, isF);
                }
                else if(S_ISREG(sourceInfo.st_mode) || S_ISLNK(sourceInfo.st_mode)){
                    char* newDestFile = malloc(strlen(newDest) + strlen(basename(newSource)));
                    if (newDestFile == NULL) {
                        perror("Erreur lors de l'allocation de mémoire");
                        free(newDestFile);
                        exit(EXIT_FAILURE);
                    }
                    sprintf(newDestFile, "%s/%s", newDest, basename(newSource));
                    copyFile(newSource, newDestFile, isA);
                    free(newDestFile);
                }
                // Libère la mémoire allouée dynamiquement
                free(newSource);
            }
        }
        free(newDest);
        // Modifier les droits du fichier ou du dossier de destination si l'option -a est activée
        if (isA) {
            if (chmod(destinationPath, sourceInfo.st_mode) < 0) {
                perror("Erreur lors de la modification des droits du fichier/dossier de destination");
                exit(EXIT_FAILURE);
            }
        }
        // Ferme le dossier source
        closedir(dir);
    }
    exit(EXIT_SUCCESS);
}