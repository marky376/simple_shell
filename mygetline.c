#include "shell.h"

/**
 * n_input_buf - buffers chained commands
 * @member: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t n_input_buf(memb_t *member, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, n_sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = n_getline(member, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			member->linecount_flag = 1;
			n_remove_comments(*buf);
			n_build_history_list(member, *buf, member->histcount++);
			{
				*len = r;
				member->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 *n_get_input - gets a line without the newline
 *@member: parameter struct
 *Return: bytes read
 */
ssize_t n_get_input(memb_t *member)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(member->arg), *p;

	n_putchar(BUF_FLUSH);
	r = n_input_buf(member, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		n_check_chain(member, buf, &j, i, len);
		while (j < len)
		{
			if (n_is_chain(member, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			member->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (n_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 *n_getline - gets the next line of input from STDIN
 *@member: parameter struct
 *@ptr: address of pointer to buffer
 *@length: size of preallocated ptr buffer
 *Return: s
 */
int n_getline(memb_t *member, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = n_read_buf(member, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = n_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = n_realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		n_strncat(new_p, buf + i, k - i);
	else
		n_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}


/**
 * n_read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: r
 */
ssize_t n_read_buf(memb_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 *n_sigintHandler - blocks ctrl - C
 *@sig_num: th signal number
 *Return: void
 */
void n_sigintHandler(__attribute__((unused))int sig_num)
{
	n_puts("\n");
	n_puts("#cisfun$ ");
	n_putchar(BUF_FLUSH);
}
