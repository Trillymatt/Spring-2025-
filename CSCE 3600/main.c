// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <termios.h>
#include "shell.h"

int main(int argc, char *argv[]) {

    tcsetpgrp(STDIN_FILENO, getpid());

    signal(SIGINT, SIG_IGN); // Ignores Ctrl-C
    signal(SIGTSTP, SIG_IGN); // Ignores Ctrl-Z
    init_paths();

    if (argc == 1) {
        // Interactive mode
        shell_loop(stdin, 1);
    } else if (argc == 2) {
        // Batch mode
        FILE *batch_file = fopen(argv[1], "r");
        if (!batch_file) {
            perror("Error opening batch file");
            exit(1);
        }
        shell_loop(batch_file, 0);
        fclose(batch_file);
    } else {
        fprintf(stderr, "Usage: %s [batch_file]\n", argv[0]);
        exit(1);
    }

    reset_system_path();

    return 0;
}
