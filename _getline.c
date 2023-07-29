#include "shell.h"

/**
 * _getline - a function that works like the standard getline function
 * @lineptr: a pointer to a pointer to a character buffer
 * @n: a pointer to the size_t variable
 * @stream: a file stream from which the input will be read
 * Return: number of characters
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char *buffer;
	static size_t bufsize;
	static size_t char_count;
	char *line;
	int c;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);
	if (buffer == NULL || char_count >= bufsize)
	{	bufsize = (bufsize == 0) ? INITIAL_BUFF_SIZE : bufsize * 2;
		buffer  = (char *)realloc(buffer, bufsize);
		if (buffer == NULL)
		{	fprintf(stderr, "Error: Memory allocation failed.\n");
			return (-1);
		}
	}
	line = buffer + char_count;
	while ((c = fgets(stream)) != EOF && c != '\n')
	{	*line++ = c;
		char_count++;
		if (char_count >= bufsize)
		{	bufsize *= 2;
			free(buffer);
			buffer = (char *)realloc(buffer, bufsize);
			if (buffer == NULL)
			{	fprintf(stderr, "Error: Memory allocation failed.\n");
				return (-1);
			}
			line = buffer + char_count;
		}
	}
	*line = '\0';
	char_count++;
	if (char_count == 1)
	{
		return (-1);
	}
	*lineptr = buffer;
	*n = bufsize;
	return (char_counts);
}
