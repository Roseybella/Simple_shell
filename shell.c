#include "main.h"


/**
 * shell_loop - the main loop of our simple shell
 * @state: the state of our programm (shell)
 * Return: eachtime (0) if success & 1 if fail
 */

int shell_loop(state_t *state)
{
	int built_in_ret = -1;

	signal(SIGINT, sigint_handler);
	while (1)
	{
		if (get_line(state) == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 2);
			break;
		}
		state->line_count++;
		if (get_commands(state) == NULL)
		{
			if (state->argv[0])
			{
				built_in_ret = locate_builtin(state);
				if (built_in_ret != -1)
				{
				if (built_in_ret == -2)
					{
				if (state->exit_number != -1)
					state->status = state->exit_number;
						break;
					}
				}
				else
				{
					issue_error(state, "not found\n");
					state->status = 127;
				}
			}
			free_state(state);
			continue;
		}
		exec_command(state);
		free_state(state);
	}
	free_state(state);
	return (state->status);
}

/**
 * get_commands - functions that set the cmd
 * @state: the state of our program (shell)
 * Return: eachtime, the line & NULL if error
 */

char **get_commands(state_t *state)
{
	char **argv;
	char *command;

	if (!state->line)
		return (NULL);

	argv = split(state->line, " \t\n");
	if (!argv)
		return (NULL);

	state->argv = argv;

	command = find_path(_getenv(state, "PATH"), argv[0]);

	while (!command)
	{
		free(state->line);
		free(state->argv);
		state->line = NULL;
		state->argv = NULL;
		return (NULL);
	}

	state->command = command;

	return (state->argv);
}



/**
 * get_line - function that set the line
 * @state: the state of our program (shell)
 * Return: eachtime, the line & NULL if error
 */

char *get_line(state_t *state)
{
	int r;
	char *real_line;
	size_t line_size = 0;

	if (isatty(STDIN_FILENO))
	{
		fflush(stdin);
		write(STDOUT_FILENO, "$ ", 2);
	}

	r = getline(&state->line, &line_size, stdin);

	if (r == EOF)
		return (NULL);

	if (state->line[r - 1] == '\n')
		state->line[r - 1] = '\0';

	real_line = remove_comments(state->line);
	if (!real_line)
		return (NULL);

	free(state->line);

	state->line = real_line;

	return (real_line);
}

/**
 * sigint_handler - function that handles the signal
 * @signal: the  signal
 */

void sigint_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n$ ", 3);
}
