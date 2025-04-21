// shell.h
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>

#define MAX_LINE 512
#define MAX_PATHS 128
#define MAX_HISTORY 20
#define MAX_ALIASES 100

void shell_loop(FILE *input_stream, int interactive);
char **parse_commands(char *line, int *num_commands);
char **parse_args(char *command);
void execute_commands(char **commands, int num_commands);

int handle_builtin(char **args);
extern int should_exit;

// Path management
extern char *paths[MAX_PATHS];
extern int path_count;
void init_paths();
void update_system_path();
void reset_system_path();

extern char *history[MAX_HISTORY];
extern int history_count;
void add_to_history(const char *line);
void clear_history();
void print_history();
char *get_history_command(int index);

void handle_pipeline(char *command_line);

typedef struct {
	char *name;
	char *command;
} Alias;

extern Alias alias_list[MAX_ALIASES];
extern int alias_count;

void handle_alias(char **args);
char *resolve_alias(const char *input);

#endif
