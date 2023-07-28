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
/**
 * _strcmp - a function used to compare two strings
 * @str1: string pointer 1
 * @str2: string pointer 2
 * Return: the difference between the strings
 */
int _strcmp(const char *str1, const char *str2)
{
	if (str1 == NULL || str2 == NULL)
	{
		return (-1);
	}
	while (*str1 != '\0' || *str2 != '\0')
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}
	return (0);
}
/**
 * _getenv - a function usd to retrieve the value of an environment variable
 * @name: string representing the name of the environment variable that
 * you want to retrieve
 * Return: NULL if variable is not found
 */
char *_getenv(const char *name)
{
	int a;
	char *delim;
	char *_var;
	size_t var_len;

	if (name == NULL || name[0] == '\0')
	{
		return (NULL);
	}
	for (a = 0; environ[a] != NULL; a++)
	{
		_var = environ[a];
		delim = strchr(_var, '=');

		if (delim == NULL || delim == _var)
		{
			continue;
		}
		var_len = delim - _var;
		if (strncmp(_var, name, var_len) == 0)
		{
			return (delim + 1);
		}
	}
	return (NULL);
}
/**
 * _strcat - a function used to concatenate two null-terminated strings
 * @src: source string
 * @dest: destination string
 * Return: destination string
 */
char *_strcat(char *dest, const char *src)
{
	char *p = dest;

	while (*p != '\0')
	{
		p++;
	}
	while (*src != '\0')
	{
		*p = *src;
		p++;
		src++;
	}
	*p = '\0';

	return (dest);
}
