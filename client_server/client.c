#include "common.h"
#include "fonctions.h"

int main(int argc, char *argv[]) {
    // Check that the server IP address and port are provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server IP> <port>\n", argv[0]);
        return -1;
    }
    // Process command line arguments
    char* server_ip = argv[1]; // Server IP
    int port = convertPort(argv[2]); // Convert argument to port
    if (port == -1){
        perror("Port conversion error");
        return -1;
    }

    struct sockaddr_in serv_addr; // Structure for server address
    int sock = 0; // File descriptor for client socket

    /** 1. Create a socket (socket) **/
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("\nSocket creation error");
        return -1;
    }
    // Configure address structure
    serv_addr.sin_family = AF_INET; // Address type (IPv4)
    serv_addr.sin_port = htons(port); // Server port

    // Convert server IP address from text to binary
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) { // returns 1 success, 0 invalid address, -1 invalid family
        perror("\nInvalid address or family\n");
        return -1;
    }

    /** 2. Connect socket to server (connect) **/
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }
    banniereClient();

    /** 3. Read/Write from socket (read/write) **/

    jouerDevinette(sock);

    /** 4. Close socket (close) **/
    close(sock); // Close client socket
    return 0;
}
