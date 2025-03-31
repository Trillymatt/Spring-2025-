//Matthew Norman
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s pattern input_file output_file\n", argv[0]);
        exit(1);
    }

    char *pattern = argv[1];
    char *input_file = argv[2];
    char *output_file = argv[3];

    int fd_in = open(input_file, O_RDONLY);
    if (fd_in < 0) {
        perror("open input_file");
        exit(1);
    }

    // Redirect stdin to input_file
    dup2(fd_in, STDIN_FILENO);   // <--- 1st system call
    close(fd_in);                // <--- 2nd system call

    int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) {
        perror("open output_file");
        exit(1);
    }

    // Redirect stdout to output_file
    dup2(fd_out, STDOUT_FILENO); // <--- 3rd system call
    close(fd_out);               // <--- 4th system call

    execlp("grep", "grep", pattern, NULL);
    perror("execlp");
    exit(1);
}
