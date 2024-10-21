#include "func.h"

// Fonction pour exécuter les commandes intégrées (builtins)
int execute_builtin(int argc, char *argv[]) {
    if (strncmp(argv[0], "cd", 2) == 0) {
        // Gestion de la commande 'cd'
        if (argc == 1) {
            chdir(getenv("HOME"));  // Aller au répertoire HOME si aucun chemin n'est fourni
        } 
        else {
            if (chdir(argv[1]) != 0) { //changer de répertoire
                // Erreur : Le répertoire n'existe pas ou l'accès est refusé
                perror("cd");
            }
        }
    } 
    else if (strncmp(argv[0], "exit", 4) == 0) {
        // Gestion de la commande 'exit'
        exit(EXIT_SUCCESS);
    } 
    else {
        return 0; // Commande non reconnue comme builtin
    }
    return 1; // Commande builtin reconnue et exécutée
}

void parse_input(char *input, char *argv[], int *argc, int max_args, int* background) {
    *argc = 0;
    *background = 0;
    char *ptr = input;
    char *start = NULL;
    int in_quotes = 0;

    while (*ptr && *argc < max_args) {
        if (*ptr == '\'' && !in_quotes) {
            // Début d'une chaîne entre guillemets
            start = ++ptr;  // Commencer après le guillemet
            in_quotes = 1;
        } else if (*ptr == '\'' && in_quotes) {
            // Fin d'une chaîne entre guillemets
            *ptr = '\0';  // Terminer la chaîne
            if (start) argv[(*argc)++] = start;  // Ajouter l'argument
            in_quotes = 0;
            start = NULL;
        } else if (*ptr == ' ' && !in_quotes) {
            // Fin d'un argument hors guillemets
            *ptr = '\0';
            if (start) argv[(*argc)++] = start;  // Ajouter l'argument
            start = NULL;
        } else if (!start) {
            // Début d'un nouvel argument
            start = ptr;
        }
        ptr++;
    }
    
    // Ajouter le dernier argument s'il existe
    if (start && *argc < max_args) argv[(*argc)++] = start;

    // Null-terminer le tableau d'arguments
    argv[*argc] = NULL;

    //tache en backgroud si & est trouvé à la fin
    if (*argc > 0 && strncmp(argv[*argc - 1], "&", 1) == 0) {
        *background = 1;
        argv[--(*argc)] = NULL; // remplace & par NULL de fin
    }
}

int execute_command(char *argv[], ShellState* shellState) {    
    pid_t pid;
    int status;

    pid = fork(); // Crée un processus enfant pour exécuter la commande
    if (pid == 0) {  // Si c'est le processus enfant
        if (shellState->background) {
            // Redirige l'entrée standard vers /dev/null pour les processus en arrière-plan
            int fd = open("/dev/null", O_WRONLY);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            if (dup2(fd, STDIN_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(fd);
        }
        // Exécute la commande
        execvp(argv[0], argv);
        // Si execvp échoue, le code suivant sera exécuté
        perror("execvp");
        exit(EXIT_FAILURE); 
    } else if (pid > 0) {  // Si c'est le processus parent
        if (shellState->background) {
            // Gère les processus en arrière-plan
            if (shellState->num_background_jobs < MAX_BACKGROUND_JOBS) {
                // Ajoute le PID du processus enfant à la liste des jobs en arrière-plan
                shellState->background_jobs[shellState->num_background_jobs++] = pid;
            } else {
                printf("Nombre maximum de jobs en arrière-plan atteint.\n");
            }
        } else {
            // Gère les processus en avant-plan
            shellState->foreground_job = pid;
            waitpid(pid, &status, 0); // Attend que le processus enfant se termine

            if (WIFEXITED(status)) {  // Vérifie si le processus s'est terminé normalement
                int exit_status = WEXITSTATUS(status);  // Récupère le code de sortie
                printf("Foreground job terminé avec le code %d\n", exit_status);
            } else {
                printf("Foreground job anormalement terminé\n");
            }
        }
    } else {
        perror("fork"); 
        return -1;
    }
    // Retourne le statut de sortie du processus en avant-plan, 0 pour les processus en arrière-plan
    return shellState->background ? 0 : WEXITSTATUS(status);
}

#ifdef USE_READLINE
// Fonction de complétion personnalisée
char** my_completion(const char *text, int start, int end) {
    rl_attempted_completion_over = 1;  // Indiquer à readline de ne pas effectuer de complétion supplémentaire
    return rl_completion_matches(text, rl_filename_completion_function);  // Utiliser la fonction de complétion de fichier de readline
}
#endif

// Gestion des signaux
void setup_signal_handlers() {
    struct sigaction sa;

    // Ignorer SIGTERM et SIGQUIT
    sa.sa_handler = SIG_IGN;
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);

    // Gérer SIGINT (interrompre le processus en avant-plan)
    sa.sa_handler = handle_sigint;
    sigaction(SIGINT, &sa, NULL);

    // Gérer SIGHUP (terminer le shell et tous les processus)
    sa.sa_handler = handle_sighup;
    sigaction(SIGHUP, &sa, NULL);

    // Gérer SIGCHLD pour les processus en arrière-plan
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = child_process_signal;
    sigaction(SIGCHLD, &sa, NULL);
}

void handle_sigint(int signum) {
    syslog(LOG_INFO, "Signal SIGINT reçu. Terminaison du processus (PID %d) en avant-plan.\n", shellState.foreground_job);
    if (shellState.foreground_job > 0) {
        kill(shellState.foreground_job, SIGINT);
    }
}

void handle_sighup(int signum) {
    syslog(LOG_INFO, "Signal SIGHUP reçu. Terminaison des processus en cours d'exécution.\n");

    // Parcourir et envoyer SIGHUP à chaque processus en arrière-plan
    for (int i = 0; i < shellState.num_background_jobs; i++) {
        if (shellState.background_jobs[i] != 0) {
            kill(shellState.background_jobs[i], SIGHUP);
        }
    }
    // Vérifiez si un travail en avant-plan est en cours d'exécution
    if (shellState.foreground_job > 0) {
        kill(shellState.foreground_job, SIGTERM);
    }
    exit(EXIT_SUCCESS); // Sortir proprement du shell
}

void child_process_signal(int signum, siginfo_t* siginfo, void* context) {
    int status;
    for (int i = 0; i < shellState.num_background_jobs; i++) {
        if (shellState.background_jobs[i] == siginfo->si_pid) {
            waitpid(siginfo->si_pid, &status, 0);
            syslog(LOG_INFO, "Processus en arrière-plan (PID %d) terminé.\n", siginfo->si_pid);
            // Déplacer les jobs restants pour combler l'espace
            for (int j = i; j < shellState.num_background_jobs - 1; j++) {
                shellState.background_jobs[j] = shellState.background_jobs[j + 1];
            }
            shellState.num_background_jobs--;
            break;
        }
    }
}
