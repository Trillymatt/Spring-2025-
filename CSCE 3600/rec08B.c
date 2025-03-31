//Matthew Norman
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file pattern\n", argv[0]);
        exit(1);
    }

    char *input_file = argv[1];
    char *pattern = argv[2];

    int pipe1[2];
    int pipe2[2];

    pipe(pipe1);
    pipe(pipe2);

    if (fork() == 0) {
        // First child: cat input_file
        int fd_in = open(input_file, O_RDONLY);
        dup2(fd_in, STDIN_FILENO);    // 1
        close(fd_in);                 // 2

        dup2(pipe1[1], STDOUT_FILENO); // 3
        close(pipe1[0]);              // 4
        close(pipe1[1]);              // 5
        close(pipe2[0]);              // 6
        close(pipe2[1]);              // 7

        execlp("cat", "cat", NULL);
        perror("execlp cat");
        exit(1);
    }

    if (fork() == 0) {
        // Second child: grep pattern
        dup2(pipe1[0], STDIN_FILENO);  // 8
        dup2(pipe2[1], STDOUT_FILENO); // 9

        close(pipe1[0]);              // 10
        close(pipe1[1]);              // 11
        close(pipe2[0]);              // 12
        close(pipe2[1]);              // 13

        execlp("grep", "grep", pattern, NULL);
        perror("execlp grep");
        exit(1);
    }

    if (fork() == 0) {
        // Third child: cut -b 1-10
        dup2(pipe2[0], STDIN_FILENO);  // 14

        close(pipe1[0]);              // 15
        close(pipe1[1]);              // 16
        close(pipe2[0]);              // 17
        close(pipe2[1]);              // 18

        execlp("cut", "cut", "-b", "1-10", NULL);
        perror("execlp cut");
        exit(1);
    }

    // Parent process closes all fds
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    // Wait for all children (optional for safety)
    for (int i = 0; i < 3; i++) wait(NULL);

    return 0;
}
