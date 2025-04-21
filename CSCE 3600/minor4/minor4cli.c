
// Matthew Norman 11701426
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024
#define NUM_PINGS 10

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s <hostname> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *hostname = argv[1];
    char *port = argv[2];
    struct addrinfo hints, *res, *p;
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct timeval start, end;
    double rtts[NUM_PINGS];
    int received = 0;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; 
    hints.ai_socktype = SOCK_DGRAM;

    if (getaddrinfo(hostname, port, &hints, &res) != 0) {
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }

    for (p = res; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd != -1)
            break;
    }

    if (!p) {
        fprintf(stderr, "Failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_PINGS; i++) {
        snprintf(buffer, sizeof(buffer), "PING");

        gettimeofday(&start, NULL);
        sendto(sockfd, buffer, strlen(buffer), 0, p->ai_addr, p->ai_addrlen);
        printf("%d: Sent... ", i + 1);

        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(sockfd, &fds);

        struct timeval timeout = {1, 0}; // 1 second timeout

        int ret = select(sockfd + 1, &fds, NULL, NULL, &timeout);
        if (ret > 0 && FD_ISSET(sockfd, &fds)) {
            int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
            gettimeofday(&end, NULL);

            double rtt = (end.tv_sec - start.tv_sec) * 1000.0;
            rtt += (end.tv_usec - start.tv_usec) / 1000.0;

            rtts[received++] = rtt;
            printf("RTT=%.6f ms\n", rtt);
        } else {
            printf("Timed Out\n");
        }
    }

    double sum = 0, min = 1e9, max = 0;
    for (int i = 0; i < received; i++) {
        sum += rtts[i];
        if (rtts[i] < min) min = rtts[i];
        if (rtts[i] > max) max = rtts[i];
    }

    double avg = received ? sum / received : 0;
    printf("%d pkts xmited, %d pkts rcvd, %d%% pkt loss\n", NUM_PINGS, received, (NUM_PINGS - received) * 100 / NUM_PINGS);
    if (received)
        printf("min: %.6f ms, max: %.6f ms, avg: %.6f ms\n", min, max, avg);

    freeaddrinfo(res);
    close(sockfd);
    return 0;
}
