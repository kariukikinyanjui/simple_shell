#include "shell.h"

/**
 * my_strtok - functions that works similarly to the standard strtok function
 * @str: input string to be tokenized
 * @delim: delimiter used to separate tokens
 * Return: token which points to the start of the current token
 */
char *my_strtok(char *str, const char *delim)
{
	static char *ptr;
	char *token;

	if (str != NULL)
	{
		ptr = str;
	}
	if (ptr == NULL)
	{
		return (NULL);
	}
	while (*ptr && strchr(delim, *ptr))
	{
		ptr++;
	}
	if (*ptr == '\0')
	{
		ptr = NULL;
		return (NULL);
	}
	token = ptr;

	while (*ptr && !strchr(delim, *ptr))
	{
		ptr++;
	}
	if (*ptr)
	{
		*ptr = '\0';
		ptr++;
	}
	return (token);
}
