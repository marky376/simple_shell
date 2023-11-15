#include "shell.h"

/**
 *n_list_len - function that determines length of linked list
 *@j: a pointer to first node
 *Return: size of list
 */
size_t n_list_len(const list_t *j)
{
	size_t i = 0;

	while (j)
	{
		j = j->next;
		i++;
	}
	return (i);
}

/**
 *n_list_to_strings - function that returns arr of strings of te list->str
 *@head: pointer to first node
 *Return: array of strings
 */
char **n_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = n_list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(n_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = n_strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 *n_print_list - function that print the whole linked list
 *@j: pointer to first node
 *Return: size of list
 */
size_t n_print_list(const list_t *j)
{
	size_t i = 0;

	while (j)
	{
		n_puts(n_convert_number(j->num, 10, 0));
		n_putchar(':');
		n_putchar(' ');
		n_puts(j->str ? j->str : "(nil)");
		n_puts("\n");
		j = j->next;
		i++;
	}
	return (i);
}

/**
 *n_node_starts_with - function thst returns node whose string starts with pref
 *@node: pointer to list head
 *@prefix: string to match
 *@c: the next char after prefix to match
 *Return: the matched node or null
 */
list_t *n_node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = n_starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 *n_get_node_index - func that gets the index of a node
 *@head: pointer to first node
 *@node: pointer to the node
 *Return: the index of the node if successfull else -1
 */
ssize_t n_get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
