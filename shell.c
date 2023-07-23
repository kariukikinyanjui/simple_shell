#include "shell.h"

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0
 */


int main(int ac, char *av[])
{
	char *prompt = "(myShell)$ ";
	char *command = NULL;
	char *argv[MAX_ARGS];
	char *commands[MAX_COMMANDS];
	size_t bufsize = BUFF_SIZE;
	ssize_t cmdread;
	int exit_status;
	int a, num_commands;
	(void)ac;
	(void)av;

	while (1)
	{
		write(STDOUT_FILENO, prompt, strlen(prompt));
		cmdread = getline(&command, &bufsize, stdin);

		if (cmdread == -1)
		{
			write(STDOUT_FILENO, "/n", 1);
			break;
		}
		command[strcspn(command, "\n")] = '\0';
		num_commands = commands_separator(command, commands);

		for (a = 0; a < num_commands; a++)
		{
			parse_func(commands[a], argv);
			if (_strcmp(argv[0], "exit") == 0)
			{
				if (argv[1] != NULL)
				{
					exit_status = atoi(argv[1]);
					free(command);
					exit_func(exit_status);
				}
				else
				{
					free(command);
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
				file_path(argv);
			}
		}
	}
	free(command);
	return (0);
}
