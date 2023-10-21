#include "main.h"

/**
 * wr_exit - function that exits our simple shell program
 * @state: the state of the program (shell)
 *  Return: eachtime, (-2) if succesful & (1) if fail
 */

int wr_exit(state_t *state)
{
	int exitnum;

	if (state->argv[1])
	{
		exitnum = _atoi(state->argv[1]);
		if (exitnum == -1)
		{
			state->status = 2;
			issue_error(state, "Illegal number: ");
			write(2, state->argv[1], _strlen(state->argv[1]));
			write(2, "\n", 1);
			return (1);
		}
		state->exit_number = exitnum;
		return (-2);
	}
	state->exit_number = -1;
	return (-2);
}


/**
 * wr_env - function that prints the current environ
 * @state: the state of our program (shell)
 * Return: eachtime (0)
 */

int wr_env(state_t *state)
{
	print_link_list(state->env_list);
	return (0);
}

/**
 * wr_setenv - function that initialize or modify env
 * @state: get_environ
 *  Return: eachtime (0) if success & (1) fail
 */

int wr_setenv(state_t *state)
{
	if (!state->argv[1]
	|| !state->argv[2])
	{
		write(2, "Incorrect number of arguements\n", 31);
		state->status = 1;
		return (1);
	}
	if (_kitenv(state, state->argv[1], state->argv[2]))
	{
		state->status = 0;
		return (0);
	}

	state->status = 1;
	return (1);
}

