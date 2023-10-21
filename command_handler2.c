#include "main.h"

/**
 * list_len - function that list the length of nodes
 * @h: the head
 * Return: eachtime, nodes
 */

size_t list_len(const list_t *h)
{
	size_t numberOfNodes = 0;

	if (!h)
		return (0);

	while (h)
	{
		h = h->next;
		numberOfNodes++;
	}

	return (numberOfNodes);
}


/**
 * wr_unsetenv - function that remove env
 * @state: the state of our programm (shel)
 *  Return: eachtime  (0) if success (1) if fail
 */

int wr_unsetenv(state_t *state)
{
	int w;

	if (!state->argv[1])
	{
		write(2, "Too few arguements.\n", 20);

		state->status = 1;
		return (1);
	}
	for (w = 1; state->argv[w]; w++)
	{
		state->status = _unkitenv(state, state->argv[w]) == 0 ? state->status : 1;
	}
	return (0);
}
