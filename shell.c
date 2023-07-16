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
	(void)ac;

	while (1)
	{
		printf("%s", prompt);
		cmdread = getline(&command, &bufsize, stdin);

		if (cmdread == -1)
		{
			printf("\n");
			break;
		}

		parse_func(command, argv);

		if (strcmp(argv[0], "exit") == 0)
		{
			exit_func();
		}
		else if (strcmp(argv[0], "env") == 0)
		{
			env_func();
		}
		else
		{
			av[0] = argv[0];
			file_path(command);
		}
	}

	free(command);
	return (0);
}
