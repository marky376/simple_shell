#include "shell.h"

/**
 * n_is_cmd - determines if a file is an executable command
 * @member: the member struct
 * @path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int n_is_cmd(memb_t *member, char *path)
{
	struct stat st;

	(void)member;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * n_dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping inde
 * Return: pointer to new buffer
 */
char *n_dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * n_find_path - finds this cmd in the PATH string
 * @member: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *n_find_path(memb_t *member, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((n_strlen(cmd) > 2) && n_starts_with(cmd, "./"))
	{
		if (n_is_cmd(member, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = n_dup_chars(pathstr, curr_pos, i);
			if (!*path)
				n_strcat(path, cmd);
			else
			{
				n_strcat(path, "/");
				n_strcat(path, cmd);
			}
			if (n_is_cmd(member, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
