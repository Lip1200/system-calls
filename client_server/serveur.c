#include "common.h"
#include "fonctions.h"

int main(int argc, char *argv[]) {
    // Vérification du nombre d'arguments passés au programme
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return -1;
    }
    int port = convertPort(argv[1]); // Conversion de l'argument en numéro de port
    if (port == -1){
        perror("Erreur de convertion de port");
        return -1;
    }

    int server_fd, socket_client; // Descripteurs de fichier pour le socket serveur et le socket client
    struct sockaddr_in address; // Structure pour l'adresse du serveur
    int addrlen = sizeof(address); // Taille de la structure d'adresse

    /** 1. Création du socket serveur (socket) **/
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return -1;
    }
    // Paramétrage du socket
    address.sin_family = AF_INET; // Type d'adresse (IPv4)
    address.sin_addr.s_addr = INADDR_ANY; // Accepte les connexions de n'importe quelle adresse
    address.sin_port = htons(port); // Port du serveur

    /** 2. Liaison du socket à l'adresse et au port (bind) **/
    if (bind(server_fd, (struct sockaddr*)&address, addrlen) < 0) {
        perror("bind failed");
        return -1;
    }
    /** 3. Prépare le socket à accepter des connexions entrantes (listen) - mise en écoute -**/
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return -1;
    }
    banniereServeur();
    while(1){
        /** 4. Accepte une connexion et obtient un socket client (accept) **/
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        if ((socket_client = accept(server_fd, (struct sockaddr*)&client_addr, &client_len)) < 0) {
            perror("accept");
            return -1;
        }
        printf("\nClient %d connecté, avec l'IP %s\n", socket_client, inet_ntoa(client_addr.sin_addr));

        /** FORK **/
        // Création d'un processus enfant pour gérer la connexion
        int status;
        pid_t pid = fork();
        if(pid > 0) wait(&status) ; // parent  --> attendant la fin du processus enfant
        else if(pid == 0){
            pid_t sub_pid = fork();
            if(sub_pid > 0) exit(EXIT_SUCCESS);
            else if(sub_pid == 0){ // enfant --> gérant la logique du jeu
                /** 5. Logique de jeu "devine un nombre" **/
                gererConnexion(socket_client, genererNombreAleatoire());
                /** 6. Fermeture du socket client **/
                close(socket_client);
            }else{
                perror("problème de sub_Fork");
                return -1;
            }
        }else{
            perror("Problème de Fork()");
            return -1;
        }
    }

    /** 7. Répétition de l'acceptation des connexions si nécessaire **/

    /** 8. Fermeture du socket serveur **/
    close(server_fd);
    return 0;
}
