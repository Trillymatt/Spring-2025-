// rec09svr.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 9000
#define BACKLOG 10

int main() {
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buffer[] = "Server Message: SUCCESS";

    listenfd = socket(AF_INET, SOCK_STREAM, 0);  // create socket
    if (listenfd < 0) {
        perror("socket");
        exit(1);
    }

    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));  // reuse address

    memset(&servaddr, 0, sizeof(servaddr));  // zero out struct
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  // any incoming interface
    servaddr.sin_port = htons(PORT);  // port to listen on

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(listenfd, BACKLOG) < 0) {
        perror("listen");
        exit(1);
    }

    while (1) {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        if (connfd < 0) {
            perror("accept");
            continue;
        }
        write(connfd, buffer, strlen(buffer));
        close(connfd);
    }

    return 0;
}
