#include "shell.h"

/**
 *n_strncpy - function copies a string
 *@dest: destination string
 *@src: source string
 *@n: amount chars
 *Return: the concanated string
 */
char *n_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *str = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 *n_strncat - function that concatenates two strings
 *@dest: destination string
 *@src: source string
 *@n: amount of chars
 *Return: the concatenated string
 */
char *n_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *str = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (str);
}

/**
 *n_strchr - func that locates a chars in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: a pointer to the memory area
 */
char *n_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
