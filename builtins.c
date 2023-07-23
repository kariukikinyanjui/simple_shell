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

/**
 * _setenv - A function that implements the 'setenv' built-in command
 * @argv: array of character pointers representing the arguments passed
 */
void _setenv(char *argv[])
{
	if (setenv(argv[1], argv[2], 1) == 0)
	{
		printf("The environment variable has been set successfully\n");
	}
	else
	{
		perror("Error setting environment variable.");
	}
}

/**
 * _unsetenv - A function that implements the 'unsetenv' built-in command
 * @argv: array of character pointers representing the arguments passed
 */
void _unsetenv(char *argv[])
{
	if (unsetenv(argv[1]) == 0)
	{
		printf("The environment variable's been unset successfully\n");
	}
	else
	{
		perror("Failed to unset environment variable.");
	}
}
