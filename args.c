#include "shell.h"

/**
 * parse_func - tokenizes the command string using spaces, tabs and
 * newlines as delimiters
 * @command: pointer to the command string to be parsed
 * @argv: an array of character pointers where the parsed
 * argument will be stored
 */
void parse_func(char *command, char *argv[])
{
	char *token = strtok(command, " \t\n");
	int argc = 0;

	while (token != NULL && argc < MAX_ARGS - 1)
	{
		argv[argc] = token;
		argc++;
		token = strtok(NULL, " \t\n");
	}
	argv[argc] = NULL;
}
