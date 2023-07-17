#include "shell.h"

/**
 * exit_func - a function that implements the exit built-in command
 * @status: exit status
 */
void exit_func(int status)
{
	exit(status);
}
/**
 * env_func - a function that implements the env built-in command
 * @argv: array of character pointers representing the arguments passed
 * to the env command
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
