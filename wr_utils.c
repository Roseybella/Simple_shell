#include "main.h"

/**
 * free_array - function that free allocated string
 * @array: Array to be freed
 * @start: starting point
 */

void free_array(char **array, int start)
{
	int w;

	for (w = start; array[w] != NULL; w++)
	{
		free(array[w]);
	}

	free(array);
}

/**
 * print_array - functions that print strings with indice
 * @array: Array of strings
 */


void print_array(char **array)
{
	int w;

	for (w = 0; array[w] != NULL; w++)
	{
		printf("[%d] -> %s", w, array[w]);
	}
}


/**
 * free_state - function that frees up memory
 * @state: the state of our programm (shell)
 */

void free_state(state_t *state)
{
	if (state == NULL)
		return;

	if (state->argv)
	{
		free_array(state->argv, 0);
		state->argv = NULL;
	}

	if (state->environ)
	{
		free_array(state->environ, 0);
		state->environ = NULL;
	}

	if (state->command)
	{
		free(state->command);
		state->command = NULL;
	}

	if (state->line)
	{
		free(state->line);
		state->line = NULL;
	}
}

/**
 * _atoi - function that converts a string to an int
 * @s: the string
 * Return: eachtime, the number, (-1) if fails
 */

int _atoi(char *s)
{
	int w = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (w = 0;  s[w] != '\0'; w++)
	{
		if (s[w] >= '0' && s[w] <= '9')
		{
			result *= 10;
			result += (s[w] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * issue_number - function that prints out number
 * @n: our shell number to print
 * @fd: our file discreptor
 * Return: eachtime (void)
 */

void issue_number(int n, int fd)
{
	unsigned int temp = n;
	char digit;

	if (n < 0)
	{
		write(fd, "-", 1);
		temp = -n;
	}

	if (temp >= 10)
		issue_number(temp / 10, fd);

	digit = temp % 10 + '0';
	write(fd, &digit, 1);
}


