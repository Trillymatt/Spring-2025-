// execution.c
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include "shell.h"

void execute_commands(char **commands, int num_commands) {
    for (int i = 0; i < num_commands; i++) {
	char *cmd = strdup(commands[i]);
	if (strchr(cmd, '|')) {
		handle_pipeline(cmd);
		free(cmd);
		continue;
	}

	char *cmd_alias = resolve_alias(cmd);
	if (cmd_alias) {
		free(cmd);
		cmd = strdup(cmd_alias);
		if (!cmd) {
			fprintf(stderr, "Memory allocation failed\n");
			continue;
		}
	}

        char **args = parse_args(cmd);
        if (args[0] == NULL) {
            free(cmd);
            free(args);
            continue;
        }

	if (handle_builtin(args)) {
		free(cmd);
		free(args);
		continue;
	}

	// Check for redirection
	int in_redirect = -1, out_redirect = -1;
	for (int j = 0; args[j]; j++) {
		if (strcmp(args[j], "<") == 0) {
			in_redirect = j;
		} else if (strcmp(args[j], ">") == 0) {
			out_redirect = j;
		}
	}

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            free(cmd);
            free(args);
	    continue;
   	}

	if (pid == 0) {

	    	// Child process

		// Put in its own process group
		setpgid(0, 0);

		// Give terminal control to child process group
		tcsetpgrp(STDIN_FILENO, getpid());

		// Restoree default aignal handling
		signal(SIGINT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);

		// Handle input redirection
   	    	if (in_redirect != -1 && args[in_redirect + 1]) {
			int fd_in = open(args[in_redirect + 1], O_RDONLY);
			if (fd_in < 0) {
				perror("open (input)");
				exit(1);
			}
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
			args[in_redirect] = NULL;
	    	}

		// Handles output redirection
	    	if (out_redirect != -1 && args[out_redirect + 1]) {
			int fd_out = open(args[out_redirect + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_out < 0) {
				perror("open (output)");
				exit(1);
			}
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			args[out_redirect] = NULL;
	    	}

            	execvp(args[0], args);
            	perror("execvp failed");
            	exit(1);
        } else {
		// --- Parent (shell) ---
		setpgid(pid, pid); // Puts child in its own group
		tcsetpgrp(STDIN_FILENO, pid); // Gives terminal control to child

		waitpid(pid, NULL, 0); // Waits for child to finish

		tcsetpgrp(STDIN_FILENO, getpid()); // Shell regains control
	}

        free(cmd);
        free(args);
    }
}

void handle_pipeline(char *command_line) {
    char *commands[3] = {NULL, NULL, NULL};
    int num_commands = 0;

    char *token = strtok(command_line, "|");
    while (token && num_commands < 3) {
	// Trim leading spaces
	while (*token == ' ') token++;
	commands[num_commands++] = token;
	token = strtok(NULL, "|");
    }

    int pipes[2][2]; // Support up to 2 pipes
    pid_t pids[3];
    pid_t pgid = 0; // Process group ID for pipeline

    for (int i = 0; i < num_commands; i++) {
	if (i < num_commands - 1) {
		if (pipe(pipes[i % 2]) == -1) {
			perror("pipe failed");
			exit(1);
		}
	}

	pids[i] = fork();
	if (pids[i] < 0) {
		perror("fork failed");
		exit(1);
   	}

	if (pids[i] == 0) {
		// --- Child Process ---

		// Sets procces group: first child sets pgid re
		if (i == 0) {
			setpgid(0, 0);
		} else {
			setpgid(0, pgid);
		}

		// Give terminal to child group
		tcsetpgrp(STDIN_FILENO, getpgrp());

		// Default signal behavior
		signal(SIGINT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);

		// Redirect input
		if (i > 0) {
			dup2(pipes[(i + 1) % 2][0], STDIN_FILENO);
		}

		// Redirects output
		if (i < num_commands - 1) {
			dup2(pipes[i % 2][1], STDOUT_FILENO);
		}

		// Close all pipes
		close(pipes[0][0]); close(pipes[0][1]);
		close(pipes[1][0]); close(pipes[1][1]);

		// Parse and execute command
		char *cmd_copy = strdup(commands[i]);
		if (!cmd_copy) {
			fprintf(stderr, "Memory error\n");
			exit(1);
		}

		char **args = parse_args(cmd_copy);
		execvp(args[0], args);
		fprintf(stderr, "Command not found: %s\n", args[0]);
		exit(1);
	} else {
		// --- Parent Process ---
		if (i == 0) {
			pgid = pids[i]; // First child becomes group leader
		}
		setpgid(pids[i], pgid); // Ensures all children join the group
	}

    }

    // Parent gives terminal to the child process group
    tcsetpgrp(STDIN_FILENO, pgid);

    // Close all pipes in parent
    close(pipes[0][0]); close(pipes[0][1]);
    close(pipes[1][0]); close(pipes[1][1]);

    // Wait for children
    for (int i = 0; i < num_commands; i++) {
	waitpid(pids[i], NULL, 0);
    }

    // Shell regains terminal control
    tcsetpgrp(STDIN_FILENO, getpid());
}
