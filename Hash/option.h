#ifndef OPTIONS_H
#define OPTIONS_H
#include <openssl/evp.h>

/**
 * @brief Analyse les options de la ligne de commande et définit les indicateurs et les indices correspondants.
 * 
 * Cette fonction analyse les options de la ligne de commande fournies par l'utilisateur et définit
 * les indicateurs et les indices correspondants en fonction des options. La fonction prend en charge
 * les options suivantes :
 * 
 * - `-f` : Définit l'indicateur isFile à 1 et stocke l'index dans indFile.
 * - `-t` : Définit l'indicateur isT à 1 et stocke l'index dans indT. De plus, vérifie et stocke
 * le type de hachage spécifié.
 * 
 * @param argc Nombre d'arguments de la ligne de commande.
 * @param argv Tableau des arguments de la ligne de commande.
 * @param isFile Pointeur vers un indicateur entier pour l'option de fichier.
 * @param indFile Pointeur vers une variable entière pour stocker l'index de l'option de fichier.
 * @param isT Pointeur vers un indicateur entier pour l'option de type de hachage.
 * @param indT Pointeur vers une variable entière pour stocker l'index de l'option de type de hachage.
 * 
 * @return 0 si l'analyse est réussie, -1 s'il y a une erreur dans les options.
 * 
 * @warning Cette fonction modifie les valeurs pointées par isFile, indFile, isT et indT.
 */
int parseOptions(int argc, char* argv[], int* isFile, int* indFile, int* isT, int* indT);

#endif /* OPTIONS_H */
