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
#define WISH_ARG_MAX 32  // Renamed from ARG_MAX to avoid conflict with system macro
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
 * Executes shell built-in commands.
 * 
 * @param argc Number of arguments.
 * @param argv Array of command arguments.
 * @return 1 if command is a built-in and was executed, 0 otherwise.
 */
int execute_builtin(int argc, char *argv[]);

/**
 * Parses user input and splits it into arguments.
 * 
 * @param input Input string to parse.
 * @param argv Array to store extracted arguments.
 * @param argc Pointer to store number of extracted arguments.
 * @param max_args Maximum number of arguments to extract.
 * @param background Pointer to indicate if command should run in background.
 */
void parse_input(char *input, char *argv[], int *argc, int max_args, int* background);

/**
 * Executes a non-built-in command.
 * 
 * @param argv Array of command arguments.
 * @param shellState Current shell state.
 * @return Exit status of executed command, or 0 if command is in background.
 */
int execute_command(char *argv[], ShellState* shellState);
#ifdef USE_READLINE

/** If readline is installed:
 * Custom completion function for readline.
 * 
 * @param text Text to complete.
 * @param start Start position of completion.
 * @param end End position of completion.
 * @return Array of strings matching possible completions.
 */
char **my_completion(const char *text, int start, int end);
#endif

// Signal handler function declarations
/**
 * Configures signal handlers for the shell.
 */
void setup_signal_handlers(void);

/**
 * Handler for SIGINT signal.
 * 
 * @param signum Signal number.
 */
void handle_sigint(int signum);

/**
 * Handler for SIGHUP signal.
 * 
 * @param signum Signal number.
 */
void handle_sighup(int signum);

/**
 * Handler for SIGCHLD signals from background processes.
 * 
 * @param signum Signal number.
 * @param siginfo Signal information.
 * @param context Signal context.
 */
void child_process_signal(int signum, siginfo_t *siginfo, void *context);

#endif //FUNC_H
