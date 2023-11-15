#include "shell.h"

/**
 *n_getenv - gets the value of an environ variable
 *@member: Struct containing all the needed arguments
 *@c: env variable name
 *Return: the value gotten
 */
char *n_getenv(memb_t *member, const char *c)
{
	list_t *node = member->env;
	char *b;

	while (node)
	{
		b = n_starts_with(node->str, c);
		if (b && *b)
			return (b);
		node = node->next;
	}
	return (NULL);
}

/**
 *n_myenv - function that prints the current environment
 *@member: Struct containing all the needed arguments
 *Return: always 0
 */
int n_myenv(memb_t *member)
{
	n_print_list_str(member->env);
	return (0);
}

/**
 *n_mysetenv - initialize a new environment or modify an existing one
 *@member: Struct containing all the needed arguments
 *Return: always success
 */
int n_mysetenv(memb_t *member)
{
	if (member->argc != 3)
	{
		n_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (n_setenv(member, member->argv[1], member->argv[2]))
		return (0);
	return (1);
}

/**
 *n_myunsetenv - function that removes an environment variable
 *@member: Struct containing all the needed arguments
 *Return: always 0
 */
int n_myunsetenv(memb_t *member)
{
	int i;

	if (member->argc == 1)
	{
		n_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= member->argc; i++)
		n_unsetenv(member, member->argv[i]);

	return (0);
}

/**
 *n_populate_env_list - function that populates env linked list
 *@member: Struct containing all the needed arguments
 *Return: 0
 */
int n_populate_env_list(memb_t *member)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		n_add_node_end(&node, environ[i], 0);
	member->env = node;
	return (0);
}
