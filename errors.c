#include "shell.h"

/**
 * _eputs - an input string should print
 * @str: string to print
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes char c to stderr
 * @c: char to print
 *
 * Return: On success 1.
 * On error, return -1, and errno is appropriately set.
 */
int _eputchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		i = 0;
		write(2, buf, i);
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes char c to fd given
 * @fd: filedescriptor to write to
 * * @c: char to print
 *
 * Return: On success 1.
 * On error, return -1, and errno is appropriately set.
 */
int _putfd(char c, int fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - input string should print
 * @str: print the string
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
