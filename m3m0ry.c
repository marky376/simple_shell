#include "shell.h"

/**
 * n_bfree - frees a pointer and NULLs the address
 * @p: address of the pointer to free
 * Return: 1 if freed success, otherwise 0.
 */
int n_bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
