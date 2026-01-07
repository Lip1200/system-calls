#ifndef TP3_FUNC_H
#define TP3_FUNC_H
#include <fcntl.h>
#include <sys/types.h>

// Definition of Commandes structure
typedef struct Commandes {
    char cmd;    // Command ('g', 's', 'w')
    char l_type; // Lock type ('r', 'w', 'u')
    int start;   // Lock start position
    int length;  // Lock length
    char whence; // Relative position ('s', 'c', 'e')
} Commandes;

/**
 * @brief Displays help for program usage.
 *
 * This function displays instructions on how to use the program,
 * detailing the command format to enter for manipulating file locks.
 */
void printHelp(void);


/**
 * @brief Parses user-entered command and configures the flock structure.
 *
 * This function takes a Commandes structure containing user command details as input,
 * and configures a flock structure according to the command parameters.
 *
 * @param comm Pointer to Commandes structure containing command details.
 * @param cmdLock Pointer to integer to store the lock command type.
 * @param fl Pointer to flock structure that will be configured according to command.
 * @return int Returns 0 on success, -1 on error.
 */
int parseComm(struct Commandes* comm, int* cmdLock, struct flock* fl);


/**
 * @brief Displays information about set or existing locks.
 *
 * Based on the command and fcntl status, this function displays detailed
 * information about current locks or those that have just been modified on the file.
 *
 * @param pid ID of the currently running process.
 * @param commande Type of lock command performed.
 * @param fl flock structure containing lock details.
 */
void lockInfos(int pid, int commande, struct flock* fl);



#endif // TP3_FUNC_H
