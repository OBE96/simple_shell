#include "shell.h"

/**
 * list_len - to find lenght of linked list
 * @h: first node pointer
 *
 * Return: list size
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns array of strings of list->str
 * @head: first node pointer
 *
 * Return: strings array
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	char *str;
	char **strs;
	size_t i = list_len(head), j;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		strs[i] = str;
		str = _strcpy(str, node->str);
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all the elements of a list_t linked list
 * @h: first node pointer
 *
 * Return: list size
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		_putchar(':');
		_putchar(' ');
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @prefix: string to match
 * @node: list head pointer
 * @c: next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the node index
 * @head: list head pointer
 * @node: node pointer
 *
 * Return: -1 or index of node
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
