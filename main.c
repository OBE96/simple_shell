#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 1 on error, 0 on success
 */
int main(int ac, char **av)
{
	int fd = 2;
	info_t info[] = { INFO_INIT };

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(": 0: Can't open ");
				_eputs(av[0]);
				_eputchar('\n');
				_eputs(av[1]);
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	hsh(info, av);
	read_history(info);
	return (EXIT_SUCCESS);
}
