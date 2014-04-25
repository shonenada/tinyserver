#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>


#define WEB_PORT 8080


void handle_connection(int sockfd, struct sockaddr_in * client_addr_ptr) {
    unsigned char *ptr = NULL, request[500];

    int length = recv(sockfd, request, 500, 0);

    printf("%s", request);

    ptr = strstr(request, " HTTP/");

    if (ptr == NULL) {
        printf("GET\n");
    }
    else {
        *ptr = 0;
        ptr = NULL;
        printf("test\n");
    }
    shutdown(sockfd, SHUT_RDWR);
}


int main (int argc, char *argv[]) {

    int i;
    int sock_fd, client_fd;

    socklen_t client_addr_len;
    
    struct sockaddr_in server_addr, client_addr;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd == -1) {
        printf("Cannot create socket\n");
        exit(1);
    }

    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(WEB_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int br = bind(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if (br == -1) {
        printf("Cannot bind the socket!\n");
        exit(1);
    }

    if ((listen(sock_fd, 20)) == -1) {
        printf("Cannot listen the socket!\n");
        exit(1);
    }

    while (1) {
        client_fd = accept(sock_fd, (struct sockaddr *) &client_addr, &client_addr_len);
        if (client_fd == -1) {
            printf("Wating for connection\n");
        }
        handle_connection(client_fd, &(client_addr));
    }

    return 0;
}