#include "func.h"

struct ShellState shellState;

int main() {
    setup_signal_handlers();

    //declarations des variables 
    char* argv[ARG_MAX];
    int argc;
    char* user = getenv("USER");
    if (!user) user = "user";  // Utiliser un nom par défaut si USER n'est pas défini
    char* prompt;
    #ifdef USE_READLINE
    char* userInput;  // Déclarer userInput seulement si USE_READLINE est défini
    #else
    char userInput[USER_INPUT_SIZE];  // Utiliser un tampon statique si readline n'est pas disponible
    #endif

    #ifdef USE_READLINE
    // Configure la fonction de complétion
    rl_attempted_completion_function = my_completion;
    #endif

    while (1) {
        char *currentDir = getcwd(NULL, 0);  // Allocation dynamique
        if (currentDir == NULL) {
            perror("Erreur getcwd");
            continue;
        }

        asprintf(&prompt, ANSI_VERT "%s" ANSI_MAGENTA "@wish [ %s ]:\n" ANSI_VERT "wi$h" ANSI_RESET "  " SYMBOL_COEUR "  ", user, currentDir);

        #ifdef USE_READLINE
        char* userInput = readline(prompt);  // Lire l'entrée avec readline
        #else
        printf("%s", prompt);
        if (fgets(userInput, USER_INPUT_SIZE, stdin) == NULL) {
            free(prompt);
            continue;
        }
        userInput[strlen(userInput) - 1] = '\0';  // Enlever le retour à la ligne
        #endif

        free(prompt);  // Libérer la mémoire allouée par asprintf

        #ifdef USE_READLINE
        if (!userInput) break;  // Sortir si Ctrl-D est pressé
        #endif

        if (strlen(userInput) == 0) {
            free(currentDir);
            continue;  // Si aucune commande n'est entrée
        }

        #ifdef USE_READLINE
        add_history(userInput);  // Ajouter à l'historique si non vide
        #endif

        parse_input(userInput, argv, &argc, ARG_MAX, &shellState.background);
        if (argc > 0) {
            if (!execute_builtin(argc, argv)) {
                execute_command(argv, &shellState);
            }
        }

        #ifdef USE_READLINE
        free(userInput);  // Libère la mémoire allouée par readline
        #endif
        free(currentDir);  // Libère la mémoire allouée par getcwd
    }
    return 0;
}
