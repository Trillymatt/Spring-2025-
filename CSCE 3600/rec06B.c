// Matthew Norman
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    char *name;

    if (pid < 0) {
        perror("fork error"); 
        exit(1);
    } else if (pid == 0) {
        
        printf("Child: PID = %d started\n", getpid());
        printf("Child: Parent PID = %d\n", getppid());
        printf("Child: Going to sleep for 20 seconds...\n");
        sleep(20);
        printf("Child: Woke up! My parent should now be init/systemd.\n");
    } else {
        
        printf("Parent: PID = %d started\n", getpid());
        printf("Parent: Parent PID = %d\n", getppid());
        printf("Parent: Terminating now.\n");
        exit(0);
    }

    name = (pid == 0) ? "Child" : "Parent";
    printf("%s: Terminating...\n", name);
    return 0;
}
