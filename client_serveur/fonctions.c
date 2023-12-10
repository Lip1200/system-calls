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
        perror("Impossible de convertir le port en Int");
        return -1;
    }
    if (port < 1024) {
        perror("Numéro de port trop petit");
        return -1;
    }
    if (port > 65535) {
        perror("Numéro de port trop élevé");
        return -1;
    }
    return port;
}

int genererNombreAleatoire() {
    unsigned char aleatoire;
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        perror("Echec d'ouverture de /dev/urandom");
        return -1;
    }
    if (read(fd, &aleatoire, sizeof(aleatoire)) == -1) {
        perror("Erreur de lecture du nombre");
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
    // Génération du nombre aléatoire
    if (valeurMystere < 0) {
        perror("Erreur de génération aléatoire du nombre mystère");
        exit(EXIT_FAILURE);
    }
    // Affiche la valeur mystère pour le suivi (log)
    printf("La valeur %d est choisie pour le client %d \n\n", valeurMystere, socket_client);

    // Envoi des bornes au client
    snprintf(buff, BUFFER_SIZE, "min=%d, max=%d", 0, MAX_GUESS);
    write(socket_client, buff, BUFFER_SIZE);

    // Boucle pour gérer les tentatives du client
    for (tentative = 0; tentative < MAX_TENTATIVES; ++tentative) {
        ssize_t n_read = read(socket_client, buff, BUFFER_SIZE); // Lit la proposition du client
        if (n_read < 0) {
            perror("read error");
            break;
        } else if (n_read == 0) {
            printf("Le client %d a fermé la connexion.\n", socket_client);
            break;
        }
        // Analyse la proposition du client
        sscanf(buff, "cmd=N/A, valeur=%d", &proposition);
        printf("Client %d propose %d\n", socket_client, proposition);
        // Appelle traiterProposition pour comparer la proposition à la valeur mystère
        cmd = traiterProposition(proposition, valeurMystere);

        if (cmd == WIN) {
            printf("Client %d a gagné\n", socket_client);
            envoyerReponse(socket_client, cmd, valeurMystere);
            break;
        } else {
            printf("Réponse envoyée au client %d :  %s\n", socket_client, (cmd == TOO_LOW ? "Trop bas" : "Trop haut"));
            envoyerReponse(socket_client, cmd, valeurMystere);
        }
    }
    if (tentative == MAX_TENTATIVES) {
        printf("Client %d a perdu\n", socket_client);
        envoyerReponse(socket_client, LOSE, valeurMystere);
    }
}

void jouerDevinette(int sock) {
    char buff[BUFFER_SIZE];
    int cmd = 0;

    // Réception des bornes de l'intervalle
    read(sock, buff, BUFFER_SIZE);
    // L'utilisateur entre sa proposition
    printf("Entrez un nombre entre %s \n> ", buff);

    while (1) {
        int proposition;
        scanf("%d", &proposition);

        // Envoi de la proposition au serveur
        snprintf(buff, BUFFER_SIZE, "cmd=N/A, valeur=%d", proposition);
        if (write(sock, buff, BUFFER_SIZE) < 0) {
            perror("write error");
            break;
        }

        // Réception de la réponse du serveur
        read(sock, buff, BUFFER_SIZE);
        sscanf(buff, "cmd=%d", &cmd);

        // Affichage des réponses
        if (cmd == TOO_LOW) {
            printf("Trop bas! Essayez à nouveau.\n");
        } else if (cmd == TOO_HIGH) {
            printf("Trop haut! Essayez à nouveau.\n");
        } else if (cmd == WIN) {
            printf("Félicitations! Vous avez gagné.\n");
            break;
        } else if (cmd == LOSE) {
            printf("Désolé, vous avez perdu.\n");
            break;
        }
    }
}
