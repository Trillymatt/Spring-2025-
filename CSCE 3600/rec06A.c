// Matthew Norman
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error"); 
        exit(1);
    } else if (pid == 0) {
        
        printf("Child process (PID: %d) is exiting.\n", getpid());
        exit(0);
    } else {
        
        printf("Parent process (PID: %d) sleeping for 5 seconds...\n", getpid());
        sleep(5);

        
        system("ps -e -o pid,ppid,stat,user,cmd | grep $USER");
    }

    return 0;
}
