#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "option.h"
#include "copy.h"
#include "func.h"


int main(int argc, char *argv[]) {

    int isA = 0; // Indicateur pour vérifier si l'option -a est sélectionnée --> modifie les droits des fichiers/dossiers
    int isF = 0; // Indicateur pour vérifier si l'option -f est sélectionnée --> liens copiés en tant que liens
    int nbOpt = 0; // Indicateur pour récupérer le nombre d'options choisies

    // Vérification des options de la ligne de commande
    if (parseOptions(argc, argv, &isA, &isF, &nbOpt) == -1) {
        fprintf(stderr, "Usage: %s [-a] [-f] source(s) destination\n", argv[0]);
        return -1;
    }

    // listing si pas assez d'arguments
    if ((argc - nbOpt) < 3){
        if((argc - nbOpt) == 2){
            listFiles(argv[nbOpt+1]); //listing depuis le repertoire en argument
        }else if ((argc - nbOpt) < 2) 
        {
            listFiles("."); // listing depuis repertoire courant si pas d'arguments
        }else{
            // signale le bon usage après avoir listé les fichiers et quitte
            fprintf(stderr, "Usage: %s source(s) destination\n", argv[0]);
            return -1;
        }
    }else{    // s'il y a deux arguments ou plus

        // Pointeur vers le dernier argument qui est la destination
        char *destination = argv[argc - 1];
        // Récupère les informations de destination
        struct stat destInfos;
        // Vérification de l'existence du répertoire de destination
        if (access(destination, F_OK) != 0) {
            // Créer le répertoire avec les permissions désirées
            // Par exemple, 0755 autorise le propriétaire à lire, écrire et exécuter, 
            // tandis que les autres peuvent seulement lire et exécuter.
            if (mkdir(destination, 0755) != 0) {
                perror("Erreur lors de la création du répertoire de destination");
                return -1;
            }
        }
        if (statInfo(destination, &destInfos, isF) < 0) {
            fprintf(stderr, "Erreur lors de l'appel fonction statInfo sur destination\n");
            return -1;
        }
        for (int i = nbOpt + 1; i < argc - 1; i++) {
            struct stat sourceInfos;
            if (statInfo(argv[i],&sourceInfos, isF)< 0) {
                fprintf(stderr, "Erreur lors de l'appel fonction statInfo la source %s\n", argv[i]);
                return -1;
            }
            // Cas où fichier ou source (reg || link) et destination reg
            if (((S_ISLNK(sourceInfos.st_mode)||(S_ISREG(sourceInfos.st_mode))) && (S_ISREG(destInfos.st_mode)))) {
                // On vérifie si la taille de la source est différente de la taille de la destination
                // ou si la date de modification de la source est antérieure à celle de la destination
                if ((sourceInfos.st_size != destInfos.st_size) || (sourceInfos.st_mtime > destInfos.st_mtime)) {
                    // Remplacer le fichier de destination par le fichier source
                    copyFile(argv[i], destination, isA);
                } else {
                    // Ne rien faire, le fichier de destination est plus récent ou de même taille que le fichier source
                    printf("%s: plus récent ou de même taille que le fichier source. Aucune action nécessaire.\n", destination);
                }
            }else if (S_ISDIR(sourceInfos.st_mode) && S_ISDIR(destInfos.st_mode)){
                // Appel la fonction pour copier le fichier/dossier
                ultraCP(argv[i], destination, isA, isF);

            }else return -1;
        }
    }
    return 0;
}

