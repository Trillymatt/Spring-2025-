// shell_core.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

void shell_loop(FILE *input_stream, int interactive) {
    char line[MAX_LINE];

    while (1) {
        if (interactive) {
            printf("myshell> ");
            fflush(stdout);
        }

        if (!fgets(line, MAX_LINE, input_stream)) break;

        if (!interactive) printf("%s", line); // Echo in batch mode

        // Remove trailing newline
        line[strcspn(line, "\n")] = '\0';

	add_to_history(line);

        int num_commands = 0;
        char **commands = parse_commands(line, &num_commands);

        execute_commands(commands, num_commands);

        // Free commands
        for (int i = 0; i < num_commands; i++) {
            free(commands[i]);
        }
        free(commands);

	if (should_exit) break;
    }
}
