#include "shell.h"

/**
 *n_get_history_file - function that gets file history
 *@member: Struct containing all the needed arguments
 *Return: allocated memory string
 */
char *n_get_history_file(memb_t *member)
{
	char *buffer, *dir;

	dir = n_getenv(member, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (n_strlen(dir) + n_strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	n_strcpy(buffer, dir);
	n_strcat(buffer, "/");
	n_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 *n_write_history - function that creates file if dont exist, otherwise appends
 *@member: Struct containing all the needed arguments
 *Return: 1 on success
 */
int n_write_history(memb_t *member)
{
	ssize_t fd;
	char *filename = n_get_history_file(member);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = member->history; node; node = node->next)
	{
		n_putsfd(node->str, fd);
		n_putfd('\n', fd);
	}
	n_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 *n_read_history - function that reads from a file
 *@member: Struct containing all the needed arguments
 *Return: histcount on success
 */
int n_read_history(memb_t *member)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = n_get_history_file(member);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			n_build_history_list(member, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		n_build_history_list(member, buf + last, linecount++);
	free(buf);
	member->histcount = linecount;
	while (member->histcount-- >= HIST_MAX)
		n_delete_node_at_index(&(member->history), 0);
	n_renumber_history(member);
	return (member->histcount);
}

/**
 *n_build_history_list - function that adds entry to a linked list
 *@member: Struct containing all the needed arguments
 *@buffer: buffer
 *@line_count: linecount for the history
 *Return: always 0
 */
int n_build_history_list(memb_t *member, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (member->history)
		node = member->history;
	n_add_node_end(&node, buffer, line_count);

	if (!member->history)
		member->history = node;
	return (0);
}

/**
 *n_renumber_history - function that renumbers th ehistory linked list changes
 *@member: Struct containing all the needed arguments
 *Return: the new histcount
 */
int n_renumber_history(memb_t *member)
{
	list_t *node = member->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (member->histcount = i);
}
