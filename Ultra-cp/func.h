#ifndef FUNC_H
#define FUNC_H

#include <stdlib.h>
#include <sys/stat.h>

/**
 * @brief Liste les fichiers et dossiers dans le répertoire spécifié.
 *
 * Cette fonction prend le chemin d'un répertoire en entrée, parcourt chaque entrée
 * dans le répertoire et affiche les détails des fichiers et dossiers.
 *
 * @param dirPath Chemin du répertoire à lister.
 */
void listFiles(const char* dirPath);

/**
 * @brief Détermine le type de fichier en fonction du mode.
 *
 * Cette fonction prend un mode de fichier en entrée et détermine le type de fichier
 * (répertoire, fichier régulier, lien symbolique, etc.).
 *
 * @param type Mode du fichier.
 * @return Caractère représentant le type de fichier ('d' pour répertoire, '-' pour fichier régulier, etc.).
 */
char fileType(mode_t type);

/**
 * @brief Convertit le mode de fichier en chaîne de caractères rwx.
 *
 * Cette fonction prend un mode de fichier en entrée et convertit les bits de permission
 * en une chaîne de caractères représentant les droits en lecture, écriture et exécution.
 *
 * @param mode Mode du fichier.
 * @return Chaîne de caractères représentant les droits en lecture, écriture et exécution (par exemple, "rwxr-xr--").
 */
char* modeToRwx(mode_t mode);

/**
 * @brief Récupère les informations sur un fichier ou un répertoire.
 *
 * Cette fonction récupère les informations sur le fichier ou le répertoire spécifié
 * par le chemin donné. Les informations sont stockées dans la structure 'struct stat'
 * pointée par 'pathInfos'. Si 'isF' est différent de zéro, les liens symboliques ne
 * sont pas déréférencés.
 *
 * @param path        Le chemin du fichier ou du répertoire.
 * @param pathInfos   Un pointeur vers 'struct stat' où les informations seront stockées.
 * @param isF         Si différent de zéro, les liens symboliques ne sont pas déréférencés.
 *
 * @return            Retourne 0 en cas de succès, -1 en cas d'échec (vérifier 'errno' pour les détails).
 */
int statInfo(char* path, struct stat* pathInfos, int isF);

#endif // FUNC_H
