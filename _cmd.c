#include "main.h"

/**
 * exec_command - funtions that execute our shell command
 * @state: the state of our program (shell)
 * Return: eachtime, (void)
 */

void exec_command(state_t *state)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(state->command, state->argv, get_env(state)) == -1)
		{
			free_state(state);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(state->status));
		if (WIFEXITED(state->status))
		{
			state->status = WEXITSTATUS(state->status);
		}
	}
}


/**
 * find_path - functions that finds  PATH string
 * @path_string: the PATH string
 * @command: what to find
 * Return: eachtime, path
 */

char *find_path(char *path_string, char *command)
{
	char **tokens, *full_path;
	int w = 0;

	if (!path_string || !command)
		return (NULL);

	if ((starts_with(command, ".") || starts_with(command, "/"))
	&& find_exec(command))
		return (_strdup(command));

	tokens = split(path_string, ":");

	while (tokens[w])
	{
		full_path = malloc(strlen(tokens[w]) + strlen(command) + 2);
		if (full_path == NULL)
		{
			w++;
			continue;
		}

		strcpy(full_path, tokens[w]);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		if (find_exec(full_path))
		{
			free_array(tokens, 0);
			return (full_path);
		}

		free(full_path);
		w++;
	}

	free_array(tokens, 0);

	return (NULL);
}


/**
 * locate_builtin - function that finds a builtin command
 * @state: the state of our program (shell)
 * Return: eachtime, -1 if not found, 0 if found, -2 exit
 */

int locate_builtin(state_t *state)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", wr_exit},
		{"env", wr_env},
		{"cd", wr_cd},
		{"setenv", wr_setenv},
		{"unsetenv", wr_unsetenv},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(state->argv[0], builtintbl[i].type) == 0)
		{
			state->command = _strdup(state->argv[0]);
			built_in_ret = builtintbl[i].func(state);
			break;
		}
	return (built_in_ret);
}

/**
 * find_exec - fucntions that determines if a file is executable
 * @file_path: the path
 * Return: eachtime (1) if YES & (0) if NO
 */

int find_exec(char *file_path)
{
	struct stat file_stat;

	if (!file_path || stat(file_path, &file_stat))
		return (0);

	if (file_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
