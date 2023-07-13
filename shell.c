#include "shell.h"

/**
 * main - Entry point
 * @prompt: prompt to be displayed continuously on a loop waiting for
 * 	    user's input
 * @command: the input gotten from the user
 * @cmdread: the input read and stored in buffer
 *
 * Return: 0
 */


int main(int ac, char *av[])
{
	char *prompt = "(myShell)$ ";  /*prompt to be displayed*/
	char *command = NULL;  /*the user's input*/
	size_t bufsize = BUFF_SIZE;
	ssize_t cmdread; /*command read from user's input*/
	pid_t pid;
	int status;

	/*declaring void variables since no arguments are going to be passed*/
	(void)ac;

	while (1)
	{
		printf("%s", prompt);
		cmdread = getline(&command, BUFF_SIZE, stdin);
		/*Handling EOF*/
		if (cmdread == -1)
		{
			printf(".....Exiting myShell.....\n");
			return (-1);
		}
		/*display the user's input*/
		printf("%s\n", command);

		av[0] = command;

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/*child process, execute command*/
			execve(av[0], av, NULL);
			perror("execve");  /*returns only if an error occurs*/
			exit(EXIT_FAILURE);
		}
		else
		{
			/*parent process*/
			waitpid(pid, &status, 0);
		}

	}
	return (0);
}
