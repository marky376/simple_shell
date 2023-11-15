#include "shell.h"

/**
 **n_memset - fills memory with a constant bytes
 *@d: pointer to the memory area
 *@b: byte to fill *d with
 *@numbs: amount of bytes to be filled
 *Return: (d) a pointer to the memory area d
 */
char *n_memset(char *d, char b, unsigned int numbs)
{
	unsigned int i;

	if (d == NULL || numbs == 0)
	{
		return (NULL);
	}

	for (i = 0; i < numbs; i++)
		d[i] = b;
	return (d);
}

/**
 * n_ffree - frees a pointer of strings
 * @dptr: double pointer strings
 * Return: nothing, void.
 */
void n_ffree(char **dptr)
{
	char **a = dptr;

	if (!dptr)
		return;
	while (*dptr)
		free(*dptr++);
	free(a);
}

/**
 * n_realloc - reallocates a block of memory
 * @ptr: pointer to previous memory allocated block
 * @_old_size: byte size of previous block
 * @_new_size: byte size of new block
 * Return: pointer to the old block.
 */
void *n_realloc(void *ptr, unsigned int _old_size, unsigned int _new_size)
{
	char *q;

	if (!ptr)
		return (malloc(_new_size));
	if (!_new_size)
		return (free(ptr), NULL);
	if (_new_size == _old_size)
		return (ptr);

	q = malloc(_new_size);
	if (!q)
		return (NULL);

	_old_size = _old_size < _new_size ? _old_size : _new_size;
	while (_old_size--)
		q[_old_size] = ((char *)ptr)[_old_size];
	free(ptr);
	return (q);
}
