#include "shell.h"

/**
 * exit_func - implementation of the exit built-in command
 * Return: exit status
 */
void exit_func(void)
{
	exit(EXIT_SUCCESS);
}
/**
 * env_func - implementation the env built-in command
 */
void env_func(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
