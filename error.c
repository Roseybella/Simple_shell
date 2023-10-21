#include "main.h"

/**
 * issue_error - function that issue out an error message
 * @state: the state of our program (shell)
 * @error: string with error
 * Return: eachtime, (0) if no numbers in string & (-1) if else
 */

void issue_error(state_t *state, char *error)
{
	write(2, state->shell_name, _strlen(state->shell_name));
	write(2, ": ", 2);
	issue_number(state->line_count, 2);
	write(2, ": ", 2);
	write(2, state->argv[0], _strlen(state->argv[0]));
	write(2, ": ", 2);
	write(2, error, _strlen(error));
}
