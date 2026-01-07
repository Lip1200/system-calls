#include "func.h"

struct ShellState shellState;

int main() {
    setup_signal_handlers();

    // Variable declarations 
    char* argv[WISH_ARG_MAX];
    int argc;
    char* user = getenv("USER");
    if (!user) user = "user";  // Use default name if USER is not defined
    char* prompt;
    #ifdef USE_READLINE
    char* userInput;  // Declare userInput only if USE_READLINE is defined
    #else
    char userInput[USER_INPUT_SIZE];  // Use static buffer if readline not available
    #endif

    #ifdef USE_READLINE
    // Configure completion function
    rl_attempted_completion_function = my_completion;
    #endif

    while (1) {
        char *currentDir = getcwd(NULL, 0);  // Dynamic allocation
        if (currentDir == NULL) {
            perror("getcwd error");
            continue;
        }

        asprintf(&prompt, ANSI_VERT "%s" ANSI_MAGENTA "@wish [ %s ]:\\n" ANSI_VERT "wi$h" ANSI_RESET "  " SYMBOL_COEUR "  ", user, currentDir);

        #ifdef USE_READLINE
        char* userInput = readline(prompt);  // Read input with readline
        #else
        printf("%s", prompt);
        if (fgets(userInput, USER_INPUT_SIZE, stdin) == NULL) {
            free(prompt);
            continue;
        }
        userInput[strlen(userInput) - 1] = '\\0';  // Remove newline
        #endif

        free(prompt);  // Free memory allocated by asprintf

        #ifdef USE_READLINE
        if (!userInput) break;  // Exit if Ctrl-D is pressed
        #endif

        if (strlen(userInput) == 0) {
            free(currentDir);
            continue;  // If no command is entered
        }

        #ifdef USE_READLINE
        add_history(userInput);  // Add to history if not empty
        #endif

        parse_input(userInput, argv, &argc, WISH_ARG_MAX, &shellState.background);
        if (argc > 0) {
            if (!execute_builtin(argc, argv)) {
                execute_command(argv, &shellState);
            }
        }

        #ifdef USE_READLINE
        free(userInput);  // Free memory allocated by readline
        #endif
        free(currentDir);  // Free memory allocated by getcwd
    }
    return 0;
}
