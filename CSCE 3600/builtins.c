// builtins.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int should_exit = 0; // global flag to indicate shell should exit

char *paths[MAX_PATHS];
int path_count = 0;
char *original_path = NULL;

char *history[MAX_HISTORY];
int history_count = 0;

Alias alias_list[MAX_ALIASES];
int alias_count = 0;

int handle_builtin(char **args) {
    if (args[0] == NULL) return 0;

    // --- CD Command ---
    if (strcmp(args[0], "cd") == 0) {
	const char *path = args[1];

	if (path == NULL) {
		path = getenv("HOME");
		if (path == NULL) {
			fprintf(stderr, "cd: HOME not set\n");
			return 1;
		}
	}

	if (chdir(path) != 0) {
		perror("cd");
	}

	return 1;
    }

    // --- EXIT Command ---
    if (strcmp(args[0], "exit") == 0) {
	should_exit = 1;
	return 1;
    }

    // --- Path Command ---
    if (strcmp(args[0], "path") == 0) {
	if (args[1] == NULL) {
		// Print current paths
		for (int i = 0; i < path_count; i++) {
			printf("%s", paths[i]);
			if (i < path_count - 1) printf(":");
		}
		printf("\n");
	} else if (strcmp(args[1], "+") == 0 && args[2]) {
		// Add new path
		if (path_count < MAX_PATHS) {
			paths[path_count++] = strdup(args[2]);
			update_system_path();
		}
	} else if (strcmp(args[1], "-") == 0 && args[2]) {
		// remove path
		for (int i = 0; i < path_count; i++) {
			if (strcmp(paths[i], args[2]) == 0) {
				free(paths[i]);
				for (int j = i; j < path_count - 1; j++) {
					paths[j] = paths[j + 1];
				}
				path_count--;
				break;
			}
		}
		update_system_path();
	} else {
		fprintf(stderr, "Usage: path [ +|- dir ]\n");
	}
	return 1; // End of path command
    }

    // --- History Command ---
    if (strcmp(args[0], "myhistory") == 0) {
	if (args[1] == NULL) {
		print_history();
	} else if (strcmp(args[1], "-c") == 0) {
		clear_history();
	} else if (strcmp(args[1], "-e") == 0 && args[2]) {
		int cmd_num = atoi(args[2]);
		char *cmd_to_run = get_history_command(cmd_num);
		if (cmd_to_run) {
			printf("Executing: %s\n", cmd_to_run);
			int num_subs;
			char **subcommands = parse_commands(strdup(cmd_to_run), &num_subs);
			execute_commands(subcommands, num_subs);

			for (int i = 0; i < num_subs; i++) {
				free(subcommands[i]);
			}
			free(subcommands);
		} else {
			fprintf(stderr, "myhistory: invalid command number\n");
		}
	} else {
		fprintf(stderr, "Usage: myhistory [-c | -e <number>]\n");
	}
	return 1;
    }

    if (strcmp(args[0], "alias") == 0) {
	handle_alias(args);
	return 1;
    }

    return 0;
}

void init_paths() {
    char *env_path = getenv("PATH");
    if (!env_path) {
	fprintf(stderr, "init_paths: PATH not found in environment.\n");
	return;
    }

    original_path = strdup(env_path);

    char *copy = strdup(env_path);
    char *token = strtok(copy, ":");
    while (token && path_count < MAX_PATHS) {
	paths[path_count++] = strdup(token);
	token = strtok(NULL, ":");
    }
    free(copy);

    update_system_path();

}

void update_system_path() {
    char new_path[4096] = "";
    for (int i = 0; i < path_count; i++) {
	strcat(new_path, paths[i]);
	if (i < path_count - 1) {
		strcat(new_path, ":");
	}
    }
    setenv("PATH", new_path, 1);
}

void reset_system_path() {
    if (original_path) {
	setenv("PATH", original_path, 1);
	free(original_path);
	original_path = NULL;
    }
}

void add_to_history(const char *line) {
    if (line == NULL || strlen(line) == 0) return;

    if (history_count >= MAX_HISTORY && history[history_count % MAX_HISTORY]) {
	free(history[history_count % MAX_HISTORY]);
    }

    history[history_count % MAX_HISTORY] = strdup(line);
    history_count++;
}

void clear_history() {
    for (int i = 0; i < MAX_HISTORY; i++) {
	if (history[i]) {
		free(history[i]);
		history[i] = NULL;
	}
    }
    history_count = 0;
}

void print_history() {
    int start = (history_count >= MAX_HISTORY) ? history_count - MAX_HISTORY : 0;
    int total = (history_count >= MAX_HISTORY) ? MAX_HISTORY : history_count;

    for (int i = 0; i < total; i++) {
	int index = (start + i) % MAX_HISTORY;
	printf("%d: %s\n", start + i + 1, history[index]);
    }
}

char *get_history_command(int index) {
    if (index < 1 || index > history_count || (history_count - index) >= MAX_HISTORY) {
	return NULL;
    }
    return history[(index - 1) % MAX_HISTORY];
}

void handle_alias(char **args) {
    if (args[1] == NULL) {
	// Print all aliases
	for (int i = 0; i < alias_count; i++) {
		printf("alias %s='%s'\n", alias_list[i].name, alias_list[i].command);
	}
	return;
    }

    if (strcmp(args[1], "-c") == 0) {
	// Clears all aliases
	for (int i = 0; i < alias_count; i++) {
		free(alias_list[i].name);
		free(alias_list[i].command);
	}
	alias_count = 0;
	return;
    }

    if (strcmp(args[1], "-r") == 0 && args[2]) {
	// Remove one alias
	for (int i = 0; i < alias_count; i++) {
		if (strcmp(alias_list[i].name, args[2]) == 0) {
			free(alias_list[i].name);
			free(alias_list[i].command);
			for (int j = i; j < alias_count - 1; j++) {
				alias_list[j] = alias_list[j + 1];
			}
			alias_count--;
			return;
		}
	}
	fprintf(stderr, "alias: alias '%s' not found\n", args[2]);
	return;
    }

    // Handle alias name='command'
    char *eq = strchr(args[1], '=');
    if (!eq || eq == args[1]) {
	fprintf(stderr, "alias: invalid format\n");
	return;
    }

    *eq = '\0';
    char *name = args[1];
    char *command = eq + 1;

    // Strip single quotes if present
    if (*command == '\'') {
	command++;
	char *end = strchr(command, '\'');
	if (end) *end = '\0';
    }

    // Check for update
    for (int i = 0; i < alias_count; i++) {
	if (strcmp(alias_list[i].name, name) == 0) {
		free(alias_list[i].command);
		alias_list[i].command = strdup(command);
		return;
	}
    }

    if (alias_count < MAX_ALIASES) {
	alias_list[alias_count].name = strdup(name);
	alias_list[alias_count].command = strdup(command);
	alias_count++;
    } else {
	fprintf(stderr, "alias: max alias limit reached\n");
    }
}

char *resolve_alias(const char *input) {
    for (int i = 0; i < alias_count; i++) {
	if (strcmp(input, alias_list[i].name) == 0) {
		return alias_list[i].command;
	}
    }
    return NULL;
}
