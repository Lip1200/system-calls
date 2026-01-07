#include "common.h"
#include "fonctions.h"

void banniereClient(void) {
    puts("   dBBBBBb    dBP dBBBBb  dBBBBb  dBP    dBBBP     dBBBBb dBBBBBb     dBBBBBBb  dBBBP");
    puts("       dBP           dBP     dBP                               BB          dBP       ");
    puts("   dBBBBK'  dBP dBP dBP dBP dBP dBP    dBBP      dBBBB     dBP BB   dBPdBPdBP dBBP   ");
    puts("  dBP  BB  dBP dBP dBP dBP dBP dBP    dBP       dB' BB    dBP  BB  dBPdBPdBP dBP     ");
    puts(" dBP  dB' dBP dBBBBBP dBBBBBP dBBBBP dBBBBP    dBBBBBB   dBBBBBBB dBPdBPdBP dBBBBP   ");
    puts("                                                                                     ");
}
void banniereServeur(void) {
    puts(".------..------..------..------.     .------..------..------..------..------..------.");
    puts("|G.--. ||A.--. ||M.--. ||E.--. |.-.  |S.--. ||E.--. ||R.--. ||V.--. ||E.--. ||R.--. |");
    puts("| :/\\: || (\\/) || (\\/) || (\\/) ( TP )| :/\\: || (\\/) || :(): || :(): || (\\/) || :(): |");
    puts("| :\\/: || :\\/: || :\\/: || :\\/: |'-.-.| :\\/: || :\\/: || ()() || ()() || :\\/: || ()() |");
    puts("| '--'G|| '--'A|| '--'M|| '--'E| ( 4 ) '--'S|| '--'E|| '--'R|| '--'V|| '--'E|| '--'R|");
    puts("`------'`------'`------'`------'  '-'`------'`------'`------'`------'`------'`------'");
}

int convertPort(const char* portStr) {
    int port = atoi(portStr);
    if (port == 0) {
        perror("Unable to convert port to Int");
        return -1;
    }
    if (port < 1024) {
        perror("Port number too small");
        return -1;
    }
    if (port > 65535) {
        perror("Port number too high");
        return -1;
    }
    return port;
}

int genererNombreAleatoire() {
    unsigned char aleatoire;
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open /dev/urandom");
        return -1;
    }
    if (read(fd, &aleatoire, sizeof(aleatoire)) == -1) {
        perror("Error reading number");
        close(fd);
        return -1;
    }
    close(fd);
    return (aleatoire % MAX_GUESS) + 1;
}

int traiterProposition(int proposition, int valeurMystere) {
    if (proposition < valeurMystere) {
        return TOO_LOW;
    } else if (proposition > valeurMystere) {
        return TOO_HIGH;
    } else {
        return WIN;
    }
}

void envoyerReponse(int socket_client, int cmd, int valeur) {
    char buff[BUFFER_SIZE];
    snprintf(buff, BUFFER_SIZE, "cmd=%d, valeur=%d", cmd, valeur);
    write(socket_client, buff, BUFFER_SIZE);
}

void gererConnexion(int socket_client, int valeurMystere) {
    char buff[BUFFER_SIZE];
    int proposition, cmd, tentative;
    // Generate random number
    if (valeurMystere < 0) {
        perror("Error generating random mystery number");
        exit(EXIT_FAILURE);
    }
    // Display mystery value for logging
    printf("Value %d is chosen for client %d \\n\\n", valeurMystere, socket_client);

    // Send bounds to client
    snprintf(buff, BUFFER_SIZE, "min=%d, max=%d", 0, MAX_GUESS);
    write(socket_client, buff, BUFFER_SIZE);

    // Loop to handle client attempts
    for (tentative = 0; tentative < MAX_TENTATIVES; ++tentative) {
        ssize_t n_read = read(socket_client, buff, BUFFER_SIZE); // Read client's guess
        if (n_read < 0) {
            perror("read error");
            break;
        } else if (n_read == 0) {
            printf("Client %d closed the connection.\\n", socket_client);
            break;
        }
        // Parse client's guess
        sscanf(buff, "cmd=N/A, valeur=%d", &proposition);
        printf("Client %d guesses %d\\n", socket_client, proposition);
        // Call traiterProposition to compare guess with mystery value
        cmd = traiterProposition(proposition, valeurMystere);

        if (cmd == WIN) {
            printf("Client %d won\\n", socket_client);
            envoyerReponse(socket_client, cmd, valeurMystere);
            break;
        } else {
            printf("Response sent to client %d: %s\\n", socket_client, (cmd == TOO_LOW ? "Too low" : "Too high"));
            envoyerReponse(socket_client, cmd, valeurMystere);
        }
    }
    if (tentative == MAX_TENTATIVES) {
        printf("Client %d lost\\n", socket_client);
        envoyerReponse(socket_client, LOSE, valeurMystere);
    }
}

void jouerDevinette(int sock) {
    char buff[BUFFER_SIZE];
    int cmd = 0;

    // Receive interval bounds
    read(sock, buff, BUFFER_SIZE);
    // User enters their guess
    printf("Enter a number between %s \\n> ", buff);

    while (1) {
        int proposition;
        scanf("%d", &proposition);

        // Send guess to server
        snprintf(buff, BUFFER_SIZE, "cmd=N/A, valeur=%d", proposition);
        if (write(sock, buff, BUFFER_SIZE) < 0) {
            perror("write error");
            break;
        }

        // Receive server response
        read(sock, buff, BUFFER_SIZE);
        sscanf(buff, "cmd=%d", &cmd);

        // Display responses
        if (cmd == TOO_LOW) {
            printf("Too low! Try again.\\n");
        } else if (cmd == TOO_HIGH) {
            printf("Too high! Try again.\\n");
        } else if (cmd == WIN) {
            printf("Congratulations! You won.\\n");
            break;
        } else if (cmd == LOSE) {
            printf("Sorry, you lost.\\n");
            break;
        }
    }
}
