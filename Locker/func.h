#ifndef TP3_FUNC_H
#define TP3_FUNC_H
#include <fcntl.h>
#include <sys/types.h>

// Définition de la structure Commandes
typedef struct Commandes {
    char cmd;    // Commande ('g', 's', 'w')
    char l_type; // Type de verrou ('r', 'w', 'u')
    int start;   // Position de départ du verrou
    int length;  // Longueur du verrou
    char whence; // Position relative ('s', 'c', 'e')
} Commandes;

/**
 * @brief Affiche l'aide pour l'utilisation du programme.
 *
 * Cette fonction affiche des instructions sur la façon d'utiliser le programme,
 * en détaillant le format des commandes à entrer pour manipuler les verrous sur les fichiers.
 */
void printHelp(void);


/**
 * @brief Analyse la commande entrée par l'utilisateur et configure la structure flock.
 *
 * Cette fonction prend en entrée une structure Commandes contenant les détails d'une commande utilisateur,
 * et configure une structure flock en fonction des paramètres de cette commande.
 *
 * @param comm Pointeur vers la structure Commandes contenant les détails de la commande.
 * @param cmdLock Pointeur vers un entier pour stocker le type de commande de verrouillage.
 * @param fl Pointeur vers une structure flock qui sera configurée selon la commande.
 * @return int Retourne 0 en cas de succès, -1 en cas d'erreur.
 */
int parseComm(struct Commandes* comm, int* cmdLock, struct flock* fl);


/**
 * @brief Affiche des informations sur les verrous posés ou existants.
 *
 * En fonction de la commande et du statut de fcntl, cette fonction affiche des informations
 * détaillées sur les verrous actuels ou ceux qui viennent d'être modifiés sur le fichier.
 *
 * @param pid ID du processus en cours d'exécution.
 * @param commande Type de commande de verrouillage effectuée.
 * @param fl Structure flock contenant les détails du verrou.
 */
void lockInfos(int pid, int commande, struct flock* fl);



#endif // TP3_FUNC_H
