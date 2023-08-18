#include "shell.h"

/**
 * bfree - frees a pointer and VOIDs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, 0 if otherwise.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		*ptr = NULL;
		free(*ptr);
		return (1);
	}
	return (0);
}
