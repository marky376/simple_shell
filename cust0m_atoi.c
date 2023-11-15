#include "shell.h"

/**
 *n_interactive - checks whether the current interaction
 *with a program is happening in an interactive mode
 *@memb: a struct object that will be used to access the structure
 *Return: (1) if in the interactive mode else (0)
 */
int n_interactive(memb_t *memb)
{
	return (isatty(STDIN_FILENO) && memb->readfd <= 2);
}

/**
 *n_is_delim - to check for the delimeter
 *@delimeter: delimeter to be passed
 *@z: a string that will be used to check for the delimiter
 *Return: (1) if the delimeter is found else (0)
 */
int n_is_delim(char delimeter, char *z)
{
	while (*z)
	{
		if (*z++ == delimeter)
			return (1);
	}
	return (0);
}

/**
 *n_isalpha - checks for alphabetic character
 *@b: The character to input
 *Return: (1) if p is alphabetic, else (0)
 */

int n_isalpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}


/**
 * n_atoi - converts a string to an integer
 * @str: string to be converted
 * Return: the int converted from the string
 */
int n_atoi(char *str)
{
	int x, d, n, len, f, digit;

	x = 0;
	d = 0;
	n = 0;
	len = 0;
	f = 0;
	digit = 0;

	while (str[len] != '\0')
		len++;

	while (x < len && f == 0)
	{
		if (str[x] == '-')
			++d;

		if (str[x] >= '0' && str[x] <= '9')
		{
			digit = str[x] - '0';
			if (d % 2)
				digit = -digit;
			n = n * 10 + digit;
			f = 1;
			if (str[x + 1] < '0' || str[x + 1] > '9')
				break;
			f = 0;
		}
		x++;
	}

	if (f == 0)
		return (0);

	return (n);
}
