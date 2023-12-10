#ifndef FUNC_H
#define FUNC_H
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h> 
#include <signal.h>
#include <syslog.h>


#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#define MAX_BACKGROUND_JOBS 10
#define USER_INPUT_SIZE 1024
#define ARG_MAX 32
#define ANSI_ROUGE   "\x1b[31m"
#define ANSI_VERT    "\x1b[32m"
#define ANSI_BLEU    "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_RESET   "\x1b[0m"

#define SYMBOL_COEUR "\u2665"

typedef struct ShellState {
    int background;
    pid_t foreground_job;
    pid_t background_jobs[MAX_BACKGROUND_JOBS];
    int num_background_jobs;
} ShellState;

extern struct ShellState shellState;

/**
 * Exécute les commandes intégrées au shell.
 * 
 * @param argc Nombre d'arguments.
 * @param argv Tableau des arguments de la commande.
 * @return 1 si la commande est une commande intégrée et a été exécutée, 0 sinon.
 */
int execute_builtin(int argc, char *argv[]);

/**
 * Analyse l'entrée utilisateur et la divise en arguments.
 * 
 * @param input Chaîne d'entrée à analyser.
 * @param argv Tableau pour stocker les arguments extraits.
 * @param argc Pointeur pour stocker le nombre d'arguments extraits.
 * @param max_args Nombre maximum d'arguments à extraire.
 * @param background Pointeur pour indiquer si la commande doit être exécutée en arrière-plan.
 */
void parse_input(char *input, char *argv[], int *argc, int max_args, int* background);

/**
 * Exécute une commande non intégrée.
 * 
 * @param argv Tableau d'arguments de la commande.
 * @param shellState État actuel du shell.
 * @return Statut de sortie de la commande exécutée, ou 0 si la commande est en arrière-plan.
 */
int execute_command(char *argv[], ShellState* shellState);
#ifdef USE_READLINE

/** si readline est installé:
 * Fonction de complétion personnalisée pour readline.
 * 
 * @param text Texte à compléter.
 * @param start Position de début de la complétion.
 * @param end Position de fin de la complétion.
 * @return Tableau de chaînes correspondant aux complétions possibles.
 */
char **my_completion(const char *text, int start, int end);
#endif

// Déclaration des fonctions de gestion des signaux
/**
 * Configure les gestionnaires de signaux pour le shell.
 */
void setup_signal_handlers(void);

/**
 * Gestionnaire pour le signal SIGINT.
 * 
 * @param signum Numéro du signal.
 */
void handle_sigint(int signum);

/**
 * Gestionnaire pour le signal SIGHUP.
 * 
 * @param signum Numéro du signal.
 */
void handle_sighup(int signum);

/**
 * Gestionnaire pour les signaux SIGCHLD des processus en arrière-plan.
 * 
 * @param signum Numéro du signal.
 * @param siginfo Informations sur le signal.
 * @param context Contexte du signal.
 */
void child_process_signal(int signum, siginfo_t *siginfo, void *context);

#endif //FUNC_H
