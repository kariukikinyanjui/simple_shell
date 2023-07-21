#include "shell.h"

/**
 * commands_separator - takes user input as a string and split it into
 * individual commands based on the ; separator
 * @input: character pointer to the input string containing multiple
 * commands separated by ;
 * @commands: array of character pointers that will store individual commands
 * extracted from the input
 * Return: number of commands found
 */
int commands_separator(char *input, char *commands[])
{
	int a = 0;
	char *token = my_strtok(input, ";");

	while (token != NULL && a < MAX_COMMANDS)
	{
		commands[a++] = token;
		token = my_strtok(NULL, ";");
	}
	return (a);
}
