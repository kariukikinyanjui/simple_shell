#include "shell.h"

/**
 * exec_sequential - execute commands sequentially
 * @commands: array of character pointers representing represening the commands
 * @num_commands: number of commands
 */
void exec_sequential(char *commands[], int num_commands)
{
	int a, exit_status;
	char *argv[MAX_ARGS];

	for (a = 0; a < num_commands; a++)
	{
		parse_func(commands[a], argv);
		if (_strcmp(argv[0], "exit") == 0)
		{
			if (argv[1] != NULL)
			{
				exit_status = atoi(argv[1]);
				if (exit_status >= 0 && exit_status <= 255)
				{
					exit_func(exit_status);
				}
				else
				{
					fprintf(stderr, "./hsh: exit: Illegal number: %d\n", exit_status);
				}
			}
			else
			{
				exit_func(0);
			}
		}
		else if (_strcmp(argv[0], "env") == 0)
		{
			env_func(argv);
		}
		else if (_strcmp(argv[0], "setenv") == 0)
		{
			_setenv(argv);
		}
		else if (_strcmp(argv[0], "unsetenv") == 0)
		{
			_unsetenv(argv);
		}
		else
		{
			find_exec_command(argv);
		}
	}
}
/**
 * exec_parallel - execute commands in parallel using child processes
 * @commands: array of character pointers representing the commands
 * @num_commands: number of commands
 */
void exec_parallel(char *commands[], int num_commands)
{
	int a;
	char *argv[MAX_ARGS];
	pid_t pid;

	for (a = 0; a < num_commands; a++)
	{
		parse_func(commands[a], argv);
		pid = fork();

		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			find_exec_command(argv);
			exit(EXIT_SUCCESS);
		}
	}
	for (a = 0; a < num_commands; a++)
	{
		wait(NULL);
	}
}
/**
 * parse_exec_command - parse and execute input command
 * @command: input command
 */
void parse_exec_command(char *command)
{
	char *commands[MAX_COMMANDS];
	int num_commands = commands_separator(command, commands);

	if (num_commands == 1)
	{
		exec_sequential(commands, num_commands);
	}
	else
	{
		exec_parallel(commands, num_commands);
	}
}
