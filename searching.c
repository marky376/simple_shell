#include "shell.h"

/**
 * n_clear_info - initializes memb_t structure
 * @member: structure address
 * Return: void.
 */
void n_clear_info(memb_t *member)
{
	member->arg = NULL;
	member->argv = NULL;
	member->path = NULL;
	member->argc = 0;
}

/**
 * n_set_info - initializes memb_t struct
 * @member: structure address
 * @av: argument vector
 * Return: void
 */
void n_set_info(memb_t *member, char **av)
{
	int i = 0;

	member->fname = av[0];
	if (member->arg)
	{
		member->argv = n_strtow(member->arg, " \t");
		if (!member->argv)
		{
			member->argv = malloc(sizeof(char *) * 2);
			if (member->argv)
			{
				member->argv[0] = n_strdup(member->arg);
				member->argv[1] = NULL;
			}
		}
		for (i = 0; member->argv && member->argv[i]; i++)
			member->argc = i;

		n_replace_alias(member);
		n_replace_vars(member);
	}
}

/**
 * n_free_info - frees info_t struct fields
 * @member: struct address
 * @all: true if freeing all fields
 * Return: void
 */
void n_free_info(memb_t *member, int all)
{
	n_ffree(member->argv);
	member->argv = NULL;
	member->path = NULL;
	if (all)
	{
		if (!member->cmd_buf)
			free(member->arg);
		if (member->env)
			n_free_list(&(member->env));
		if (member->history)
			n_free_list(&(member->history));
		if (member->alias)
			n_free_list(&(member->alias));
		n_ffree(member->environ);
			member->environ = NULL;
		n_bfree((void **)member->cmd_buf);
		if (member->readfd > 2)
			close(member->readfd);
		n_putchar(BUF_FLUSH);
	}
}
