#include "shell.h"

/**
 *n_is_chain - function that tests if char buffer
 *@member: parameter structure
 *@buffer: char buffer
 *@q: address of current position
 *Return: 1 if succes, 0 otherwise
 */
int n_is_chain(memb_t *member, char *buffer, size_t *q)
{
	size_t j = *q;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = '\0';
		j++;
		member->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = '\0';
		j++;
		member->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = '\0';
		member->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = j;
	return (1);
}

/**
 * n_check_chain - func that checks if we should continue chaining based
 * @member: the structure
 * @buffer: the char buffer
 * @q: address of current position in buffer
 * @i: starting position in buffer
 * @length: length of bufffer
 * Return: void
 */
void n_check_chain(memb_t *member, char *buffer,
		size_t *q, size_t i, size_t length)
{
	size_t j = *q;

	if (member->cmd_buf_type == CMD_AND)
	{
		if (member->status)
		{
			buffer[i] = 0;
			j = length;
		}
	}
	if (member->cmd_buf_type == CMD_OR)
	{
		if (!member->status)
		{
			buffer[i] = 0;
			j = length;
		}
	}

	*q = j;
}

/**
 *n_replace_alias - replaces an alias
 *@member: the struct
 *Return: 1 success
 */
int n_replace_alias(memb_t *member)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = n_node_starts_with(member->alias, member->argv[0], '=');
		if (!node)
			return (0);
		free(member->argv[0]);
		p = n_strchr(node->str, '=');
		if (!p)
			return (0);
		p = n_strdup(p + 1);
		if (!p)
			return (0);
		member->argv[0] = p;
	}
	return (1);
}

/**
 *n_replace_vars - replaces vars in the tokenized string
 *@member: struct
 *Return: always 1 success
 */
int n_replace_vars(memb_t *member)
{
	int i = 0;
	list_t *node;

	for (i = 0; member->argv[i]; i++)
	{
		if (member->argv[i][0] != '$' || !member->argv[i][1])
			continue;

		if (!n_strcmp(member->argv[i], "$?"))
		{
			n_replace_string(&(member->argv[i]),
				n_strdup(n_convert_number(member->status, 10, 0)));
			continue;
		}
		if (!n_strcmp(member->argv[i], "$$"))
		{
			n_replace_string(&(member->argv[i]),
				n_strdup(n_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = n_node_starts_with(member->env, &member->argv[i][1], '=');
		if (node)
		{
			n_replace_string(&(member->argv[i]),
				n_strdup(n_strchr(node->str, '=') + 1));
			continue;
		}
		n_replace_string(&member->argv[i], n_strdup(""));

	}
	return (0);
}

/**
 *n_replace_string - replaces string
 *@old: address of old string
 *@new: new string
 *Return: 1 if success, else 0
 */
int n_replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
