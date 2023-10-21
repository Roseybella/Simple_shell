#include "main.h"

/**
 * split - function that splits string with a delimiter
 * @str: string
 * @delim: program delimiter
 * Return: eachtime, the tokens
 */

char **split(char *str, char *delim)
{
	int w = 0;
	size_t tokens_size = 0;
	char **tokens = NULL;
	char *token = NULL;
	char *temp = _strdup(str);

	if (str == NULL)
		return (NULL);

	tokens_size = count_split(str, delim);

	tokens = malloc(sizeof(char *) * tokens_size);
	if (tokens == NULL)
		return (NULL);

	token = strtok(temp, delim);
	while (token != NULL)
	{
		tokens[w] = _strdup(token);
		token = strtok(NULL, delim);
		w++;
	}

	tokens[w] = NULL;
	free(temp);
	return (tokens);
}


/**
 * count_split - counts how many words splited
 * @str: string to tokenize
 * @delim: delimiter
 * Return: count
 */

size_t count_split(char *str, char *delim)
{
	size_t count = 1;
	char *temp = _strdup(str);
	char *token = NULL;

	if (str == NULL)
		return (0);

	token = strtok(temp, delim);
	while (token != NULL)
	{
		token = strtok(NULL, delim);
		count++;
	}

	free(temp);
	return (count);
}

/**
 * _strtok - functions that tokenizes a string
 * @str: string
 * @delim: program delimiter
 * Return: eachtime, the first token found
 */
char *_strtok(char *str, char *delim)
{
	static char *token;
	static char *next;
	char *delim_ptr;

	if (str != NULL)
		next = str;
	if (next == NULL)
		return (NULL);

	token = next;
	delim_ptr = _strchr(token, *delim);

	while (delim_ptr != NULL)
	{
		*delim_ptr = '\0';
		next = delim_ptr + 1;
		delim_ptr = _strchr(next, *delim);
	}

	if (next[0] == '\0')
	{
		next = NULL;
	}

	return (token);
}



