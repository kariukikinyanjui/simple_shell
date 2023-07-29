#include "shell.h"

/**
 * exit_func - a function that implements the exit built-in command
 * @status: exit status
 */
void exit_func(int status)
{
	if (status >= 0 && status <= 255)
	{
		exit(status);
	}
	else
	{
		fprintf(stderr, "./hsh: exit: Illegal number: %d\n", status);
		exit(2);
	}
}

/**
 * env_func - a function that implements the env built-in command
 */
void env_func(void)
{
	char **env = environ;
	size_t len;

	while (*env != NULL)
	{
		len = strlen(*env);
		write(STDOUT_FILENO, *env, len);
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

/**
 * _setenv - A function that implements the 'setenv' built-in command
 * @argv: array of character pointers representing the arguments passed
 */
void _setenv(char *argv[])
{
	const char *succ_msg, *err_msg;

	if (argv[1] == NULL || argv[2] == NULL)
	{
		err_msg = "setenv: missing arguments\n";
		write(STDERR_FILENO, err_msg, strlen(err_msg));
		return;
	}

	if (setenv(argv[1], argv[2], 1) == 0)
	{
		succ_msg = "The environment variable has been set successfully\n";
		write(STDOUT_FILENO, succ_msg, strlen(succ_msg));
	}
	else
	{
		err_msg = "Error setting environment variable.";
		write(STDERR_FILENO, err_msg, strlen(err_msg));
	}
}

/**
 * _unsetenv - A function that implements the 'unsetenv' built-in command
 * @argv: array of character pointers representing the arguments passed
 */
void _unsetenv(char *argv[])
{
	const char *succ_msg, *err_msg;

	if (argv[1] == NULL)
	{
		err_msg = "unsetenv: missing argument\n";
		write(STDERR_FILENO, err_msg, strlen(err_msg));
		return;
	}
	if (unsetenv(argv[1]) == 0)
	{
		succ_msg = "The environment variable's been unset successfully\n";
		write(STDOUT_FILENO, succ_msg, strlen(succ_msg));
	}
	else
	{
		err_msg = "Failed to unset environment variable.";
		write(STDERR_FILENO, err_msg, strlen(err_msg));
	}
}
