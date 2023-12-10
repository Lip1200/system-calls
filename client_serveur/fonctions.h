#ifndef TP4_FONCTIONS_H
#define TP4_FONCTIONS_H

/**
 * @brief Génère un nombre aléatoire à deviner.
 *
 * Cette fonction génère un nombre aléatoire compris entre 1 et MAX_GUESS, utilisé comme le nombre mystère dans le jeu.
 *
 * @return int Le nombre aléatoire généré.
 */
int genererNombreAleatoire(void);

/**
 * @brief Compare la proposition du joueur avec le nombre mystère.
 *
 * Cette fonction prend en entrée la proposition du joueur et la compare avec le nombre mystère.
 * Elle renvoie une indication si la proposition est trop basse, trop haute ou correcte.
 *
 * @param proposition La proposition faite par le joueur.
 * @param valeurMystere Le nombre mystère à deviner.
 * @return int Un code indiquant si la proposition est trop basse (TOO_LOW), trop haute (TOO_HIGH), ou correcte (WIN).
 */
int traiterProposition(int proposition, int valeurMystere);

/**
 * @brief Envoie une réponse au client en fonction de sa proposition.
 *
 * Cette fonction envoie une réponse au client, lui indiquant si sa proposition est trop basse, trop haute, correcte, ou si le jeu est terminé.
 *
 * @param socket_client Le socket du client auquel envoyer la réponse.
 * @param cmd Le code de réponse à envoyer (TOO_LOW, TOO_HIGH, WIN, LOSE).
 * @param valeur La valeur correcte ou la dernière proposition du joueur.
 */
void envoyerReponse(int socket_client, int cmd, int valeur);

/**
 * @brief Gère la logique du jeu pour une connexion client.
 *
 * Cette fonction gère la logique du jeu pour un client donné. Elle lit les propositions du client, appelle les fonctions pour les traiter, et envoie les réponses appropriées.
 *
 * @param socket_client Le socket du client à gérer.
 * @param valeurMystere Le nombre mystère que le client doit deviner.
 */
void gererConnexion(int socket_client, int valeurMystere);

/**
 * @brief Convertit une chaîne de caractères en un numéro de port et vérifie sa validité.
 *
 * Cette fonction convertit la chaîne de caractères fournie en un numéro de port.
 * Elle vérifie également que le port est dans une plage valide (supérieur à 1024 et inférieur à 65535).
 *
 * @param portStr La chaîne de caractères représentant le numéro de port.
 * @return int Le numéro de port après conversion et validation, ou -1 en cas d'erreur.
 */
int convertPort(const char* portStr);

/**
 * @brief Permet au client de jouer au jeu de devinettes.
 *
 * Cette fonction gère la logique du jeu côté client, en permettant à l'utilisateur
 * de faire des propositions et en affichant les réponses du serveur.
 *
 * @param sock Le descripteur de fichier du socket client.
 */
void jouerDevinette(int sock);

/**
 * @brief Affiche une bannière décorative pour le client.
 *
 * Cette fonction affiche une bannière ASCII artistique pour le client au démarrage du jeu.
 */
void banniereClient(void);

/**
 * @brief Affiche une bannière décorative pour le serveur.
 *
 * Cette fonction affiche une bannière ASCII artistique pour le serveur au démarrage du jeu.
 */
void banniereServeur(void);

#endif // TP4_FONCTIONS_H
