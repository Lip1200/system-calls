#ifndef COPY_H
#define COPY_H

/**
 * Copie le fichier spécifié depuis la source vers la destination.
 * @param sourcePath Le chemin du fichier source.
 * @param destinationPath Le chemin du fichier de destination.
 * @param isA Indicateur pour vérifier si l'option -a est activée.
 */
void copyFile(char* sourcePath, char* destinationPath, int isA);

/**
 * Copie le fichier ou le dossier spécifié depuis la source vers la destination.
 * @param sourcePath Le chemin du fichier ou du dossier source.
 * @param destinationPath Le chemin du fichier ou du dossier de destination.
 * @param isA Indicateur pour vérifier si l'option -a est activée.
 * @param isF Indicateur pour vérifier si l'option -f est activée.
 */
void ultraCP(char* sourcePath, char* destinationPath, int isA, int isF);

#endif //COPY_H
