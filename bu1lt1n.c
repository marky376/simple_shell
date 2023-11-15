#include "shell.h"

/**
 * n_myexit - function name
 * @member: argument name
 * Return: always success
 */
int n_myexit(memb_t *member)
{
	int n_exitcheck;

	if (member->argv[1])
	{
		n_exitcheck = n_erratoi(member->argv[1]);
		if (n_exitcheck == -1)
		{
			member->status = 2;
			n_print_error(member, "Wrong number: ");
			n_puts(member->argv[1]);
			n_putchar('\n');
			return (1);
		}
		member->err_num = n_erratoi(member->argv[1]);

		return (-2);
	}
	member->err_num = -1;
	return (-2);
}

/**
 * n_mycd - Changes  current directory of the process.
 * @member: Structure member containing potential arguments.
 * Return: Always success.
 */
int n_mycd(memb_t *member)
{
	char *v, *dir, buffer[1024];
	int chdir_ret;

	v = getcwd(buffer, 1024);
	if (!v)
		n_puts("ERROR: getcwd failed\n");
	if (!member->argv[1])
	{
		dir = n_getenv(member, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = n_getenv(member, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (n_strcmp(member->argv[1], "-") == 0)
	{
		if (!n_getenv(member, "OLDPWD="))
		{
			n_puts(v);
			n_putchar('\n');
			return (1);
		}
		n_puts(n_getenv(member, "OLDPWD="));
		n_putchar('\n');
		chdir_ret = chdir((dir = n_getenv(member, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(member->argv[1]);
	if (chdir_ret == -1)
	{
		n_print_error(member, "can't cd to ");
		n_puts(member->argv[1]);
		n_putchar('\n');
	}
	else
	{
		n_setenv(member, "OLDPWD", n_getenv(member, "PWD="));
		n_setenv(member, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * n_myhelp - Prints a help message for the shell.
 * @member: Structure containing potential arguments.
 * Return: Always success.
 */
int n_myhelp(memb_t *member)
{
	char **args_arr;

	args_arr = member->argv;

	n_puts("help call works. Function not yet implemented \n");

	if (0)
		n_puts(*args_arr);

	return (0);
}
