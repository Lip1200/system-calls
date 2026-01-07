#ifndef OPTION_H
#define OPTION_H

/**
 * Parses command line options.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @param isA A pointer to flag for -a option.
 * @param isF A pointer to flag for -f option.
 * @param nbOpt A pointer to options counter.
 * @return 0 on success, -1 on error.
 */
int parseOptions(int argc, char* argv[], int* isA, int* isF, int* nbOpt);

#endif //OPTION_H
