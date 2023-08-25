#include "shell.h"


/**
 * get_sigint - Handle the control plus c call in prompt
 * @sig: the Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
