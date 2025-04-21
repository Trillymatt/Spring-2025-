// parser.c
#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include "shell.h"

char **parse_commands(char *line, int *num_commands) {
    char **commands = NULL;
    int count = 0;

    char *token = strtok(line, ";");
    while (token) {
        commands = realloc(commands, sizeof(char *) * (count + 1));
        commands[count++] = strdup(token);
        token = strtok(NULL, ";");
    }

    *num_commands = count;
    return commands;
}

char **parse_args(char *command) {
    char **args = NULL;
    int count = 0;

    char *token = strtok(command, " \t");
    while (token) {
        args = realloc(args, sizeof(char *) * (count + 1));
        args[count++] = token;
        token = strtok(NULL, " \t");
    }

    args = realloc(args, sizeof(char *) * (count + 1));
    args[count] = NULL;

    return args;
}
