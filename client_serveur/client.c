#include "common.h"
#include "fonctions.h"

int main(int argc, char *argv[]) {
    // Vérification que l'adresse IP du serveur et le port sont fournis
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server IP> <port>\n", argv[0]);
        return -1;
    }
    // Traitement des arguments de la ligne de commande
    char* server_ip = argv[1]; // IP du serveur
    int port = convertPort(argv[2]); // Convertir l'argument en port
    if (port == -1){
        perror("Erreur de convertion de port");
        return -1;
    }

    struct sockaddr_in serv_addr; // Structure pour l'adresse du serveur
    int sock = 0; // Descripteur de fichier pour le socket client

    /** 1. Crée un socket (socket) **/
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("\nErreur de création de socket");
        return -1;
    }
    // Configuration de la structure d'adresse
    serv_addr.sin_family = AF_INET; // Type d'adresse (IPv4)
    serv_addr.sin_port = htons(port); // Port du serveur

    // Convertit l'adresse IP du serveur de texte en binaire
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) { //renvoie 1 succès, 0 adresse invalide et -1 famille invalide
        perror("\nAdresse ou famille invalide\n");
        return -1;
    }

    /** 2. Connecte un socket à un serveur (connect) **/
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Echec de connection");
        return -1;
    }
    banniereClient();

    /** 3. Lecture/Ecriture à parir du socket (read/write) **/

    jouerDevinette(sock);

    /** 4. Ferme le socket (close) **/
    close(sock); // Ferme le socket client
    return 0;
}
