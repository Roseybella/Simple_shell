#include "main.h"

/**
 * remove_comments - functions that remove Comments from string
 * @str: string
 * Return: eachtime, new string
 */


char *remove_comments(char *str)
{
	char *com_loc;
	char *temp_str = _strdup(str);
	char **temp_line;

	if (!temp_str)
		return (NULL);

	com_loc = _strchr(temp_str, '#');
	if (!com_loc)
		return (temp_str);

	if (com_loc == temp_str)
	{
		temp_str[0] = '\n';
		temp_str[1] = '\0';
		return (temp_str);
	}

	if (*(--com_loc) != ' ')
		return (temp_str);

	temp_line = split(temp_str, "#");
	free(temp_str);

	if (!temp_line)
		return (NULL);

	temp_str = temp_line[0];

	free_array(temp_line, 1);

	return (temp_str);
}

/**
 * _strchr - function that locates a char in string
 * @s: the string
 * @c: the char
 * Return: eachtime, char in string
 */

char *_strchr(char *s, char c)
{
	int w = 0;

	while (s[w] != '\0')
	{
		if (s[w] == c)
			break;
		w++;
	}

	if (s[w] == c)
		return (s + w);
	else
		return (NULL);
}

