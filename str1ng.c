#include "shell.h"

/**
 *n_strlen - function that return the length of a string
 *@c: the string
 *Return: integer kength
 */
int n_strlen(char *c)
{
	int i = 0;

	if (!c)
		return (0);

	while (*c++)
		i++;
	return (i);
}

/**
 *n_strcmp - function performs comparison of two strings
 *@c1: the 1st string
 *@c2: the 2nd string
 *Return: an integer
 */
int n_strcmp(char *c1, char *c2)
{
	while (*c1 && *c2)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	if (*c1 == *c2)
		return (0);
	else
		return (*c1 < *c2 ? -1 : 1);
}

/**
 *n_starts_with - checks if needle starts with haystack
 *@haystack: string to search
 *@needle: the substring to find
 *Return: address of next char of haystack or NULL
 */
char *n_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}
	return ((char *)haystack);
}

/**
 *n_strcat - function that concatenates two strings
 *@dest: the destination buffer
 *@src: the source buffer
 *Return: pointer to destination buffer
 */
char *n_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
