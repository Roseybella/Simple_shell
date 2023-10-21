#include "main.h"

/**
 * _getenv - function that gets the value of an environ variable
 * @state: the state of our program (shell)
 * @name: the name of the env var
 * Return: eachtime, the value
 */

char *_getenv(state_t *state, const char *name)
{
	list_t *node = state->env_list;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (++p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _unkitenv - function that remove the env variable
 * @state: the state of the program (shell)
 * @name: the string env name property
 * Return: eachtime, 1 if delete & (0) if else
 */

int _unkitenv(state_t *state, char *name)
{
	list_t *node = state->env_list;
	size_t w = 0;
	char *p;

	state->environ_changed = 0;

	if (!node || !name)
		return (0);

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p == '=')
		{
			state->environ_changed = remove_node(&(state->env_list), w);
			w = 0;
			node = state->env_list;
			continue;
		}
		node = node->next;
		w++;
	}
	return (state->environ_changed);
}

/**
 * _kitenv - function that modify & initialize new env
 * @state: the state of the programm (shell)
 * @name: the name of string
 * @value: the string value
 *  Return: eachtime  (0)
 */

int _kitenv(state_t *state, char *name, char *value)
{
	char *temp = NULL;
	list_t *node;
	char *p;

	if (!name || !value)
		return (0);
	temp = malloc(_strlen(name) + _strlen(value) + 2);
	if (!temp)
		return (1);

	strcpy(temp, name);
	_strcat(temp, "=");
	_strcat(temp, value);

	node = state->env_list;
	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = temp;
			state->environ_changed = 1;
			return (0);
		}
		node = node->next;
	}
	plus_node(&(state->env_list), temp);
	free(temp);
	state->environ_changed = 1;
	return (0);
}

/**
 * get_env - function that returns the string of env
 *  @state: the state of our program (shell)
 *  Return: eachtime (0)
 */

char **get_env(state_t *state)
{
	if (!state->environ || state->environ_changed)
	{
		state->environ = list_strings(state->env_list);
		state->environ_changed = 0;
	}

	return (state->environ);
}


/**
 * init_env_list - functions that populates env linked list
 *  @state: the state of our program (shell)
 *  Return: eachtime (0)
 */

int init_env_list(state_t *state)
{
	list_t *node = NULL;
	size_t w;

	for (w = 0; environ[w]; w++)
		plus_node(&node, environ[w]);
	state->env_list = node;
	return (0);
}

