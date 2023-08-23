#include "shell.h"

/**
 * hsh - loop of main shell
 * @info: parameter & return info struct
 * @av: argument vector from main()
 *
 * Return: 1 error, 0 on success.
 */
int hsh(info_t *info, char **av)
{
	int builtin_ret = 0;
	ssize_t r = 0;

	while (r != -1 && builtin_ret != -2)
	{
		if (interactive(info))
		clear_info(info);
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		if (r != -1)
		r = get_input(info);
		{
			set_info(info, av);
			if (builtin_ret == -1)
			builtin_ret = find_builtin(info);
				find_cmd(info);
		}
		if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * @info: parameter & return info struct
 * find_builtin - finds a builtin command
 *
 * Return: if builtin not found, -1
 * 	   if builtin executed successfully, 0
 * 	   if builtin found but not successful, 1
 * 	   if builtin signals exit() 2
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"help", _myhelp},
		{"env", _myenv},
		{"setenv", _mysetenv},
		{"history", _myhistory},
		{"cd", _mycd},
		{"unsetenv", _myunsetenv},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	int i, k;
	char *path = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->linecount_flag = 0;
		info->line_count++;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		fork_cmd(info);
		info->path = path;
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * @info: parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
