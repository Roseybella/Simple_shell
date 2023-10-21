#ifndef SHELL_H
#define SHELL_H


#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;
#define READ_SIZE 1024

/**
 * struct list_s - singly linked list
 * @str: string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */

typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;


/**
 * struct state_s - Holds information about the program's current state.
 *
 * @shell_name: The name of the shell program.
 * @command: The command being processed.
 * @env_list: A list of environment variables specific to the program.
 * @environ: An array of strings representing all environment variables.
 * @line: The current line of input.
 * @argv: Arguments for the current command.
 * @line_count: The count of lines processed so far.
 * @environ_changed: A flag (1 if changed) indicate if environment is modified.
 * @status: The result of the last command executed.
 * @exit_number: The status code to return when the program ends.
 */


typedef struct state_s
{
	char *shell_name;
	char *command;
	list_t *env_list;
	char **environ;
	char *line;
	char **argv;
	int line_count;
	int environ_changed;
	int status;
	int exit_number;
} state_t;



/**
 *struct builtin - function that contains a builtin string
 *@type: the builtin flag
 *@func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(state_t *);
} builtin_table;



/* Wesley/Rose Shell */

int shell_loop(state_t *state);
char *get_line(state_t *state);
char **get_commands(state_t *state);
void sigint_handler(int signal);


/* Strings  */

char *_strdup(char *src);
char *_strcat(char *dest, char *src);
char *starts_with(const char *haystack, const char *needle);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strchr(char *s, char c);
char *_strtok(char *str, char *delim);
size_t count_split(char *str, char *delim);
char **split(char *str, char *delim);
char *remove_comments(char *str);


/* Linked List */

list_t *plus_node(list_t **head, char *str);
size_t print_link_list(const list_t *h);
char **list_strings(list_t *head);
int remove_node(list_t **head, unsigned int index);
size_t list_len(const list_t *h);
void free_link_list(list_t *head);


/* Environment variables */

int init_env_list(state_t *state);
int _kitenv(state_t *state, char *name, char *value);
int _unkitenv(state_t *state, char *name);
char *_getenv(state_t *state, const char *name);
char **get_env(state_t *state);

/* Error / number */

void issue_error(state_t *state, char *error);
void issue_number(int n, int fd);

/* Utils */

void free_array(char **array, int start);
void free_state(state_t *state);
void print_array(char **array);
int _atoi(char *s);

/* builtins */

int wr_exit(state_t *state);
int wr_env(state_t *state);
int wr_cd(state_t *state);
int wr_setenv(state_t *state);
int wr_unsetenv(state_t *state);



/* Command Handlers */
char *find_path(char *path_string, char *command);
int find_exec(char *file_path);
void exec_command(state_t *state);
int locate_builtin(state_t *state);


#endif
