#ifndef HASH_H
#define HASH_H

#include <openssl/evp.h>

/**
 * @brief Calcule le hachage d'un fichier spécifié.
 * 
 * Cette fonction prend le chemin d'un fichier en entrée, calcule son hachage en utilisant
 * l'algorithme de hachage spécifié par le pointeur digest, et affiche le résultat du hachage.
 * 
 * @param file Chemin du fichier à hacher.
 * @param digest Pointeur vers l'algorithme de hachage à utiliser.
 */
void FileHash(char* file, const EVP_MD* digest);

/**
 * @brief Calcule le hachage d'une chaîne de caractères spécifiée.
 * 
 * Cette fonction prend une chaîne de caractères en entrée, calcule son hachage en utilisant
 * l'algorithme de hachage spécifié par le pointeur digest, et affiche le résultat du hachage.
 * 
 * @param input Chaîne de caractères à hacher.
 * @param digest Pointeur vers l'algorithme de hachage à utiliser.
 * @param size_input Taille de la chaîne de caractères à hacher.
 */
void StringHash(char* input, const EVP_MD* digest, int size_input);

#endif /* HASH_H */
