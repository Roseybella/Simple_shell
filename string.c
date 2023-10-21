#include "main.h"

/**
 * _strdup - function that duplicate a string
 * @src: source
 * Return: eachtime, duplicated string
 */

char *_strdup(char *src)
{
	char *str;
	char *p;
	int len = 0;

	len = _strlen(src);

	str = malloc(len + 1);
	if (!str)
		return (NULL);

	p = str;
	while (*src)
		*p++ = *src++;

	*p = '\0';
	return (str);
}

/**
 * _strlen - function that returns the length of a string
 * @s: the string
 * Return: eachtime, the length of string
 */

int _strlen(char *s)
{
	int w = 0;

	if (!s)
		return (0);

	while (*s++)
		w++;
	return (w);
}

/**
 * _strcmp - function that performs lexicogarphic comparison.
 * @s1: first string
 * @s2: second string
 * Return: eachtime, (neg) if s1 < s2, (pos)
 * if s1 > s2, zero if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}


/**
 * starts_with - function that checks with haystack
 * @wesley: the person to be searched
 * @rose: the person doing the search
 * Return: eachtime, haystack / NULL
 */

char *starts_with(const char *wesley, const char *rose)
{
	while (*rose)
		if (*rose++ != *wesley++)
			return (NULL);
	return ((char *)wesley);
}

/**
 * _strcat - fucntions that concatenates two strings
 * @dest: destination
 * @src: source
 * Return: eachtime, destination
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

