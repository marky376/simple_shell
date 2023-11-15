#include "shell.h"

/**
 * main - entry point of the function
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	memb_t member[] = { MEMB_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				n_eputs(argv[0]);
				n_eputs(": 0: Can't open ");
				n_eputs(argv[1]);
				n_eputchar('\n');
				n_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		member->readfd = fd;
	}
	n_populate_env_list(member);
	n_read_history(member);
	n_hsh(member, argv);
	return (EXIT_SUCCESS);
}
