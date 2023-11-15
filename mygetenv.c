#include "shell.h"

/**
 * n_get_environ - function of the string array copy of our environ
 * @member: Structure containing all members
 * Return: Always success
 */
char **n_get_environ(memb_t *member)
{
	if (!member->environ || member->env_changed)
	{
		member->environ = n_list_to_strings(member->env);
		member->env_changed = 0;
	}

	return (member->environ);
}

/**
 * n_unsetenv - function that removes an env't variable from the linked list.
 * @member: Structure containing all members
 * @variable: The string representing the environment variable to remove.
 * Return: 1 for success, 0- failure
 */
int n_unsetenv(memb_t *member, char *variable)
{
	list_t *node = member->env;
	size_t i = 0;
	char *q;

	if (!node || !variable)
		return (0);

	while (node)
	{
		q = n_starts_with(node->str, variable);
		if (q && *q == '=')
		{
			member->env_changed = n_delete_node_at_index(&(member->env), i);
			i = 0;
			node = member->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (member->env_changed);
}

/**
 * n_setenv - function for the new env't
 * @member: Structure containing all members
 * @variable: the string env var property
 * @val: the string env var value
 * Return: Always success 0
 */
int n_setenv(memb_t *member, char *variable, char *val)
{
	char *buffer = NULL;
	list_t *node;
	char *q;

	if (!variable || !val)
		return (0);

	buffer = malloc(n_strlen(variable) + n_strlen(val) + 2);
	if (!buffer)
		return (1);
	n_strcpy(buffer, variable);
	n_strcat(buffer, "=");
	n_strcat(buffer, val);

	node = member->env;
	while (node)
	{
		q = n_starts_with(node->str, variable);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buffer;
			member->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	n_add_node_end(&(member->env), buffer, 0);
	free(buffer);
	member->env_changed = 1;
	return (0);
}
