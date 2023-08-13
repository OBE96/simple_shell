#include "shell.h"

/**
 **_strncpy - copies a string
 *@src: source string
 *@n: amount of chars to copie
 *@dest: where the string should be copied
 *Return: concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	char *s = dest;
	int i, j;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		i++;
		dest[i] = src[i];
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - two strings concatenates
 *@dest:first string
 *@src: second string
 *@n: maxima amount of bytes to be used
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	char *s = dest;
	int i, j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a char in a string
 *@s: string to parsed
 *@c: char to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
