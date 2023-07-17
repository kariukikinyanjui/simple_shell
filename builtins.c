#include "shell.h"

/**
 * exit_func - implementation of the exit built-in command
 * @argv: pointer to a string
 * Return: exit status
 */
void exit_func(char *argv[])
{
	(void)argv;
	exit(EXIT_SUCCESS);
}
/**
 * env_func - implementation the env built-in command
 */
void env_func(char *argv[])
{
	char **env = environ;
	(void)argv;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
