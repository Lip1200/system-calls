#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <openssl/evp.h>
#include "option.h"
#include "hash.h"


void FileHash(char* file, const EVP_MD* md)
{
    // Initialiser le contexte de hachage
    EVP_MD_CTX* mdctx;
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL)
    {
        fprintf(stderr, "Erreur lors de l'initialisation du contexte de hachage.\n");
    }

    // initialisation
    if (!EVP_DigestInit_ex(mdctx, md, NULL))
    {
        printf("Erreur d'initialisation.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }
    // Ouvrir le fichier en mode lecture
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier : %s\n", file);
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    // Lire le fichier ligne par ligne et mettre à jour le hachage
    while ((read = getline(&line, &len, fp)) != -1)
    {

        if (!EVP_DigestUpdate(mdctx, line, read))
        {
            printf("Erreur de mise-à-jour du message digest.\n");
            EVP_MD_CTX_free(mdctx);
            exit(1);
        }
    }

    // Finaliser le hachage et obtenir le résultat
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    if (!EVP_DigestFinal_ex(mdctx, hash, &hash_len))
    {
        printf("Message digest finalization failed.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    // Afficher le hachage calculé
    printf("Hachage (%s) : ", EVP_MD_name(md));
    for (unsigned int i = 0; i < hash_len; ++i)
    {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // libere la memoire et ferme le fichier
    EVP_MD_CTX_free(mdctx);
    fclose(fp);
    if (line)
    {
        free(line);
    }
}

void StringHash(char* input, const EVP_MD* md, int size_input)
{
    // Initialiser le contexte de hachage
    EVP_MD_CTX *mdctx;
    mdctx = EVP_MD_CTX_new();

    if (!EVP_DigestInit_ex(mdctx, md, NULL))
    {
        printf("Erreur d'initialisation.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    // Allouer de la mémoire pour la chaîne résultante
    unsigned char *data = (unsigned char *)malloc(size_input);

    // Parcourir la chaîne de caractères input et copier les caractères avec les espaces
    int data_index = 0;
    for (int i = 0; i < size_input; ++i)
    {
        data[data_index] = input[i];
        data_index++;
    }

    // Mettre à jour le hachage avec les données
    if (!EVP_DigestUpdate(mdctx, data, size_input))
    {
        printf("Message digest update failed.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    // Finaliser le hachage et obtenir le résultat
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    if (!EVP_DigestFinal_ex(mdctx, hash, &hash_len))
    {
        printf("Message digest finalization failed.\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    // Afficher le hachage calculé
    printf("Hachage (%s) : ", EVP_MD_name(md));
    for (unsigned int i = 0; i < hash_len; ++i)
    {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // Libérer la mémoire allouée dynamiquement
    EVP_MD_CTX_free(mdctx);
    free(data);
}