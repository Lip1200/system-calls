#include "func.h"

// Function to execute built-in commands (builtins)
int execute_builtin(int argc, char *argv[]) {
    if (strncmp(argv[0], "cd", 2) == 0) {
        // Handle 'cd' command
        if (argc == 1) {
            chdir(getenv("HOME"));  // Go to HOME directory if no path provided
        } 
        else {
            if (chdir(argv[1]) != 0) { // Change directory
                // Error: Directory doesn't exist or access denied
                perror("cd");
            }
        }
    } 
    else if (strncmp(argv[0], "exit", 4) == 0) {
        // Handle 'exit' command
        exit(EXIT_SUCCESS);
    } 
    else {
        return 0; // Command not recognized as builtin
    }
    return 1; // Builtin command recognized and executed
}

void parse_input(char *input, char *argv[], int *argc, int max_args, int* background) {
    *argc = 0;
    *background = 0;
    char *ptr = input;
    char *start = NULL;
    int in_quotes = 0;

    while (*ptr && *argc < max_args) {
        if (*ptr == '\\'' && !in_quotes) {
            // Start of quoted string
            start = ++ptr;  // Start after the quote
            in_quotes = 1;
        } else if (*ptr == '\\'' && in_quotes) {
            // End of quoted string
            *ptr = '\\0';  // Terminate string
            if (start) argv[(*argc)++] = start;  // Add argument
            in_quotes = 0;
            start = NULL;
        } else if (*ptr == ' ' && !in_quotes) {
            // End of argument outside quotes
            *ptr = '\\0';
            if (start) argv[(*argc)++] = start;  // Add argument
            start = NULL;
        } else if (!start) {
            // Start of new argument
            start = ptr;
        }
        ptr++;
    }
    
    // Add last argument if exists
    if (start && *argc < max_args) argv[(*argc)++] = start;

    // Null-terminate argument array
    argv[*argc] = NULL;

    // Background task if & is found at the end
    if (*argc > 0 && strncmp(argv[*argc - 1], "&", 1) == 0) {
        *background = 1;
        argv[--(*argc)] = NULL; // Replace & with NULL terminator
    }
}

int execute_command(char *argv[], ShellState* shellState) {    
    pid_t pid;
    int status;

    pid = fork(); // Create child process to execute command
    if (pid == 0) {  // If child process
        if (shellState->background) {
            // Redirect standard input to /dev/null for background processes
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
        // Execute command
        execvp(argv[0], argv);
        // If execvp fails, following code will execute
        perror("execvp");
        exit(EXIT_FAILURE); 
    } else if (pid > 0) {  // If parent process
        if (shellState->background) {
            // Handle background processes
            if (shellState->num_background_jobs < MAX_BACKGROUND_JOBS) {
                // Add child process PID to background jobs list
                shellState->background_jobs[shellState->num_background_jobs++] = pid;
            } else {
                printf("Maximum number of background jobs reached.\\n");
            }
        } else {
            // Handle foreground processes
            shellState->foreground_job = pid;
            waitpid(pid, &status, 0); // Wait for child process to finish

            if (WIFEXITED(status)) {  // Check if process terminated normally
                int exit_status = WEXITSTATUS(status);  // Get exit code
                printf("Foreground job terminated with code %d\\n", exit_status);
            } else {
                printf("Foreground job abnormally terminated\\n");
            }
        }
    } else {
        perror("fork"); 
        return -1;
    }
    // Return exit status of foreground process, 0 for background processes
    return shellState->background ? 0 : WEXITSTATUS(status);
}

#ifdef USE_READLINE
// Custom completion function
char** my_completion(const char *text, int start, int end) {
    rl_attempted_completion_over = 1;  // Tell readline not to perform additional completion
    return rl_completion_matches(text, rl_filename_completion_function);  // Use readline's file completion function
}
#endif

// Signal handling
void setup_signal_handlers() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));  // Initialize struct to avoid undefined behavior

    // Ignore SIGTERM and SIGQUIT
    sa.sa_handler = SIG_IGN;
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);

    // Handle SIGINT (interrupt foreground process)
    sa.sa_handler = handle_sigint;
    sigaction(SIGINT, &sa, NULL);

    // Handle SIGHUP (terminate shell and all processes)
    sa.sa_handler = handle_sighup;
    sigaction(SIGHUP, &sa, NULL);

    // Handle SIGCHLD for background processes
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = child_process_signal;
    sigaction(SIGCHLD, &sa, NULL);
}

void handle_sigint(int signum) {
    syslog(LOG_INFO, "SIGINT signal received. Terminating foreground process (PID %d).\\n", shellState.foreground_job);
    if (shellState.foreground_job > 0) {
        kill(shellState.foreground_job, SIGINT);
    }
}

void handle_sighup(int signum) {
    syslog(LOG_INFO, "SIGHUP signal received. Terminating running processes.\\n");

    // Traverse and send SIGHUP to each background process
    for (int i = 0; i < shellState.num_background_jobs; i++) {
        if (shellState.background_jobs[i] != 0) {
            kill(shellState.background_jobs[i], SIGHUP);
        }
    }
    // Check if foreground job is running
    if (shellState.foreground_job > 0) {
        kill(shellState.foreground_job, SIGTERM);
    }
    exit(EXIT_SUCCESS); // Exit shell cleanly
}

void child_process_signal(int signum, siginfo_t* siginfo, void* context) {
    int status;
    for (int i = 0; i < shellState.num_background_jobs; i++) {
        if (shellState.background_jobs[i] == siginfo->si_pid) {
            waitpid(siginfo->si_pid, &status, 0);
            syslog(LOG_INFO, "Background process (PID %d) terminated.\\n", siginfo->si_pid);
            // Shift remaining jobs to fill the gap
            for (int j = i; j < shellState.num_background_jobs - 1; j++) {
                shellState.background_jobs[j] = shellState.background_jobs[j + 1];
            }
            shellState.num_background_jobs--;
            break;
        }
    }
}
