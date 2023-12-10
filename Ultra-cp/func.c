#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>

// fonction pour convertir le type mode_t en char
char fileType(mode_t type) {
    char fileType;
    switch (type & S_IFMT) {
        case S_IFDIR:
            fileType = 'd';
            break;
        case S_IFREG:
            fileType = '-';
            break;
        case S_IFLNK:
            fileType = 'l';
            break;
        default:
            fileType = '?'; // Autre type de fichier
            break;
    }
    return fileType;
}

// fonction qui convertit les permissions de fichier en format de chaîne de caractères (rwx).
char* modeToRwx(mode_t mode) {
    char* rwx = malloc(10 * sizeof(char)); // 9 caractères pour rwx et 1 pour le caractère de fin de chaîne '\0'
    if (rwx == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    // Propriétaire
    rwx[0] = (mode & S_IRUSR) ? 'r' : '-';
    rwx[1] = (mode & S_IWUSR) ? 'w' : '-';
    rwx[2] = (mode & S_IXUSR) ? 'x' : '-';

    // Groupe
    rwx[3] = (mode & S_IRGRP) ? 'r' : '-';
    rwx[4] = (mode & S_IWGRP) ? 'w' : '-';
    rwx[5] = (mode & S_IXGRP) ? 'x' : '-';

    // Autres utilisateurs
    rwx[6] = (mode & S_IROTH) ? 'r' : '-';
    rwx[7] = (mode & S_IWOTH) ? 'w' : '-';
    rwx[8] = (mode & S_IXOTH) ? 'x' : '-';

    rwx[9] = '\0'; // Ajoute le caractère de fin de chaîne à la fin

    return rwx;
}

// fonction qui liste les fichiers dans un répertoire spécifié par dirPath.
void listFiles(const char* dirPath) {
    // Ouvre le répertoire spécifié
    DIR* dir= opendir(dirPath);
    struct dirent* entry;
    struct stat fileInfos;

    // Vérifie si le répertoire est ouvert correctement
    if (dir == NULL) {
        perror("Erreur lors de l'ouverture du dossier");
        exit(EXIT_FAILURE);
    }

    // Parcourt chaque entrée dans le répertoire
    while ((entry = readdir(dir)) != NULL) {

        // Ignore les entrées "." et ".."
        if (strncmp(entry->d_name, ".", 1) != 0 && strncmp(entry->d_name, "..", 2) != 0) { //ajouter \0 et augmenter de 1 pour inclure les fichiers cachés
            // Construit le chemin complet du fichier/dossier avec malloc
            char* filePath = malloc(strlen(dirPath) + strlen(entry->d_name) + 2);
            if (filePath == NULL) {
                perror("Erreur lors de l'allocation de mémoire");
                exit(EXIT_FAILURE);
            }
            //écrit la sortie dans la chaine de caratères
            sprintf(filePath, "%s/%s", dirPath, entry->d_name);

            // Obtient les informations sur le fichier/dossier
            if (lstat(filePath, &fileInfos) < 0) {
                perror("Erreur lors de la récupération des informations du fichier");
                exit(EXIT_FAILURE);
            }
            //formatage date pour fonction strftime
            int max_size = 80;
            char dateModif[max_size];
            struct tm* mtime = localtime(&fileInfos.st_mtime);
            if (strftime(dateModif, max_size, "%a %b %d %H:%M:%S %Y", mtime) == 0) {
                fprintf(stderr, "Erreur de formatage de la date strftime()");
                exit(EXIT_FAILURE);
            }
            // Affiche les détails du fichier/dossier
            printf("%c %-10s %10ld %-10s %s \n",
                   fileType(fileInfos.st_mode), modeToRwx(fileInfos.st_mode), fileInfos.st_size, dateModif, filePath);
            if (S_ISDIR(fileInfos.st_mode))
                listFiles(filePath); //si dossier-> appel récursif-> explore le sous dossier

            free(filePath); // libère le malloc

        }
    }
    // Ferme le répertoire
    closedir(dir);
}

// fonction pour peupler la structure stat selon isF (liens copiés comme lien) ou pas (déréférencés).
int statInfo(char* path, struct stat* pathInfos, int isF){
    if (access(path, F_OK) == 0){  // Le fichier de path existe
        if(isF){ //liens copiés en tant que lien
            if (lstat(path, pathInfos) < 0) { //peuple la struct stat
                perror("Erreur lors de la récupération des informations du fichier");
                return -1;
            }
        }else{ // liens sont déréférencés
            if (stat(path, pathInfos) < 0) {
                perror("Erreur lors de la récupération des informations du fichier");
                return -1;
            }
        }
    }else return -1;
    return 0;
}