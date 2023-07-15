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
	char *token;
	size_t bufsize = BUFF_SIZE;
	ssize_t cmdread;
	int arg_count;
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
		command[strcspn(command, "\n")] = '\0';
		token = strtok(command, " ");
		arg_count = 0;

		while (token != NULL)
		{
			av[arg_count] = token;
			token = strtok(NULL, " ");
			arg_count++;
		}
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
	free(command);
	return (0);
}
