#include "shell.h"

/**
 * main - Entry point
 * @ac: function parameter 1
 * @av: function parameter 2
 * Return: 0
 */


int main(int ac, char *av[])
{
	char *prompt = "(myShell)$ ";
	char *command = NULL;
	size_t bufsize = BUFF_SIZE;
	ssize_t cmdread;
	pid_t pid;
	int status;
	(void)ac;

	while (1)
	{
		printf("%s", prompt);
		cmdread = getline(&command, &bufsize, stdin);

		if (cmdread == -1)
		{
			printf("\n");
			return (-1);
		}
		printf("%s", command);

		av[0] = command;
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execve(av[0], av, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
		}

	}
	return (0);
}
