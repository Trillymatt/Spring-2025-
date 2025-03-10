#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        // Child process exits immediately
        exit(0);
    } else {
        // Parent sleeps for 5 seconds to allow the child to become a zombie
        sleep(5);
        // Display process status
        system("ps -e -o pid,ppid,stat,user,cmd | grep $USER");
    }

    return 0;
}