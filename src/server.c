#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "settings.h"
#include "http_methods.h"
#include "server_handler.h"

#define WEB_PORT 8080

int main (int argc, char *argv[]) {

    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid != 0) {
        exit(0);
    }

    pid = setsid();
    if (pid < -1) {
        perror("setsid");
        exit(1);
    }
    int fd = open("/dev/null", O_RDWR, 0);
    if (fd == -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > 2) {
            close(fd);
        }
    }
    umask(0000);

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
        client_addr_len = sizeof(client_addr);
        client_fd = accept(sock_fd, (struct sockaddr *) &client_addr, &client_addr_len);
        if (client_fd == -1) {
            printf("Wating for connection\n");
        }
        handleConnection(client_fd, &(client_addr));
    }

    return 0;
}
