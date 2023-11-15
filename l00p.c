#include "shell.h"

/**
 *n_hsh - main shell loop
 *@member: the struct
 *@av: the argument vector from main
 *Return: 0 on success
 */
int n_hsh(memb_t *member, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		n_clear_info(member);
		if (n_interactive(member))
			n_puts("#cisfun$ ");
		n_eputchar(BUF_FLUSH);
		r = n_get_input(member);
		if (r != -1)
		{
			n_set_info(member, av);
			builtin_ret = n_find_builtin(member);
			if (builtin_ret == -1)
				n_find_cmd(member);
		}
		else if (n_interactive(member))
			n_putchar('\n');
		n_free_info(member, 0);
	}
	n_write_history(member);
	n_free_info(member, 1);
	if (!n_interactive(member) && member->status)
		exit(member->status);
	if (builtin_ret == -2)
	{
		if (member->err_num == -1)
			exit(member->status);
		exit(member->err_num);
	}
	return (builtin_ret);
}

/**
 *n_find_builtin - finds a built in comand
 *@member: te struct
 *Return: -1 if not found
 */
int n_find_builtin(memb_t *member)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", n_myexit},
		{"env", n_myenv},
		{"help", n_myhelp},
		{"history", n_myhistory},
		{"setenv", n_mysetenv},
		{"unsetenv", n_myunsetenv},
		{"cd", n_mycd},
		{"alias", n_myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (n_strcmp(member->argv[0], builtintbl[i].type) == 0)
		{
			member->line_count++;
			built_in_ret = builtintbl[i].func(member);
			break;
		}
	return (built_in_ret);
}

/**
 *n_find_cmd - find a command in path
 *@member: the struct
 *Return: void
 */
void n_find_cmd(memb_t *member)
{
	char *path = NULL;
	int i, k;

	member->path = member->argv[0];
	if (member->linecount_flag == 1)
	{
		member->line_count++;
		member->linecount_flag = 0;
	}
	for (i = 0, k = 0; member->arg[i]; i++)
		if (!n_is_delim(member->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = n_find_path(member, n_getenv(member, "PATH="), member->argv[0]);
	if (path)
	{
		member->path = path;
		n_fork_cmd(member);
	}
	else
	{
		if ((n_interactive(member) || n_getenv(member, "PATH=")
			|| member->argv[0][0] == '/') && n_is_cmd(member, member->argv[0]))
			n_fork_cmd(member);
		else if (*(member->arg) != '\n')
		{
			member->status = 127;
			n_print_error(member, "No such file or directory\n");
		}
	}
}

/**
 *n_fork_cmd - forks a exec tread to run cmd
 *@member: the struct
 */
void n_fork_cmd(memb_t *member)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(member->path, member->argv, n_get_environ(member)) == -1)
		{
			n_free_info(member, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(member->status));
		if (WIFEXITED(member->status))
		{
			member->status = WEXITSTATUS(member->status);
			if (member->status == 126)
				n_print_error(member, "Permission denied\n");
		}
	}
}
