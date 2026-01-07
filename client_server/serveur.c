#include "common.h"
#include "fonctions.h"

int main(int argc, char *argv[]) {
    // Check number of arguments passed to the program
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return -1;
    }
    int port = convertPort(argv[1]); // Convert argument to port number
    if (port == -1){
        perror("Port conversion error");
        return -1;
    }

    int server_fd, socket_client; // File descriptors for server socket and client socket
    struct sockaddr_in address; // Structure for server address
    int addrlen = sizeof(address); // Size of address structure

    /** 1. Create server socket (socket) **/
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return -1;
    }
    // Socket configuration
    address.sin_family = AF_INET; // Address type (IPv4)
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any address
    address.sin_port = htons(port); // Server port

    /** 2. Bind socket to address and port (bind) **/
    if (bind(server_fd, (struct sockaddr*)&address, addrlen) < 0) {
        perror("bind failed");
        return -1;
    }
    /** 3. Prepare socket to accept incoming connections (listen) - start listening **/
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return -1;
    }
    banniereServeur();
    while(1){
        /** 4. Accept a connection and get client socket (accept) **/
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        if ((socket_client = accept(server_fd, (struct sockaddr*)&client_addr, &client_len)) < 0) {
            perror("accept");
            return -1;
        }
        printf("\nClient %d connected, with IP %s\n", socket_client, inet_ntoa(client_addr.sin_addr));

        /** FORK **/
        // Create child process to handle connection
        int status;
        pid_t pid = fork();
        if(pid > 0) wait(&status) ; // parent --> wait for child process to finish
        else if(pid == 0){
            pid_t sub_pid = fork();
            if(sub_pid > 0) exit(EXIT_SUCCESS);
            else if(sub_pid == 0){ // child --> handling game logic
                /** 5. "Guess a number" game logic **/
                gererConnexion(socket_client, genererNombreAleatoire());
                /** 6. Close client socket **/
                close(socket_client);
            }else{
                perror("sub_Fork problem");
                return -1;
            }
        }else{
            perror("Fork() problem");
            return -1;
        }
    }

    /** 7. Repeat connection acceptance if needed **/

    /** 8. Close server socket **/
    close(server_fd);
    return 0;
}
