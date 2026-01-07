#ifndef TP4_FONCTIONS_H
#define TP4_FONCTIONS_H

/**
 * @brief Generates a random number to guess.
 *
 * This function generates a random number between 1 and MAX_GUESS, used as the mystery number in the game.
 *
 * @return int The generated random number.
 */
int genererNombreAleatoire(void);

/**
 * @brief Compares the player's guess with the mystery number.
 *
 * This function takes the player's guess as input and compares it with the mystery number.
 * It returns an indication if the guess is too low, too high, or correct.
 *
 * @param proposition The guess made by the player.
 * @param valeurMystere The mystery number to guess.
 * @return int A code indicating if the guess is too low (TOO_LOW), too high (TOO_HIGH), or correct (WIN).
 */
int traiterProposition(int proposition, int valeurMystere);

/**
 * @brief Sends a response to the client based on their guess.
 *
 * This function sends a response to the client, indicating if their guess is too low, too high, correct, or if the game is over.
 *
 * @param socket_client The client socket to send the response to.
 * @param cmd The response code to send (TOO_LOW, TOO_HIGH, WIN, LOSE).
 * @param valeur The correct value or the player's last guess.
 */
void envoyerReponse(int socket_client, int cmd, int valeur);

/**
 * @brief Handles the game logic for a client connection.
 *
 * This function handles the game logic for a given client. It reads the client's guesses, calls functions to process them, and sends appropriate responses.
 *
 * @param socket_client The client socket to handle.
 * @param valeurMystere The mystery number that the client must guess.
 */
void gererConnexion(int socket_client, int valeurMystere);

/**
 * @brief Converts a string to a port number and validates it.
 *
 * This function converts the provided string to a port number.
 * It also checks that the port is in a valid range (greater than 1024 and less than 65535).
 *
 * @param portStr The string representing the port number.
 * @return int The port number after conversion and validation, or -1 on error.
 */
int convertPort(const char* portStr);

/**
 * @brief Allows the client to play the guessing game.
 *
 * This function handles the client-side game logic, allowing the user
 * to make guesses and displaying server responses.
 *
 * @param sock The client socket file descriptor.
 */
void jouerDevinette(int sock);

/**
 * @brief Displays a decorative banner for the client.
 *
 * This function displays an ASCII art banner for the client at game startup.
 */
void banniereClient(void);

/**
 * @brief Displays a decorative banner for the server.
 *
 * This function displays an ASCII art banner for the server at game startup.
 */
void banniereServeur(void);

#endif // TP4_FONCTIONS_H
