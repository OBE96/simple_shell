#include "shell.h"

/**
 * _myexit - exit shell
 * @info: potential argument in structures. Used to maintain
 * constant function prototype.
 * Return: exit given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* For an exit argument */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			_eputs(info->argv[1]);
			print_error(info, "Illegal number: ");
			info->status = 2;
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - current directory of the process changes
 * @info: potential arguments in structures. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	int chdir_ret;
	char *s, *dir, buffer[1024];

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what will it be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_putchar('\n');
			_puts(s);
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what will it be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		_eputs(info->argv[1]), _eputchar('\n');
		print_error(info, "can't cd to ");
	}
	else
	{
		_setenv(info, "PWD", getcwd(buffer, 1024));
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
	}
	return (0);
}

/**
 * _myhelp - current directory of the process changes
 * @info: potential arguments in structures. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
