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
	size_t bufsize = BUFF_SIZE;
	ssize_t cmdread;
	int exit_status;
	(void)ac;
	(void)av;

	while (1)
	{
		printf("%s", prompt);
		cmdread = getline(&command, &bufsize, stdin);

		if (cmdread == -1)
		{
			printf("\n");
			break;
		}
		command[strcspn(command, "\n")] = '\0';

		parse_func(command, argv);

		if (strcmp(argv[0], "exit") == 0)
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
		else if (strcmp(argv[0], "env") == 0)
		{
			env_func(argv);
		}
		else
		{
			file_path(argv);
		}
	}

	free(command);
	return (0);
}
