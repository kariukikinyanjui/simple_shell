#include "shell.h"

/**
 * file_path - A function that gets the PATH environment variable of a command
 * and executes the command
 * @command: A pointer to the command from user's input
 */

void file_path(char *command)
{
	char *path, *path_copy;
	char *dir;
	char full_path[BUFF_SIZE];
	int status;

	path = getenv("PATH");
	path_copy = strdup(path);

	if (path == NULL)
	{
		printf("PATH environment variable not found\n");
		return;
	}

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		strncpy(full_path, dir, BUFF_SIZE - 1);
		full_path[BUFF_SIZE - 1] = '\0';
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, F_OK) == 0)
		{
			pid_t pid = fork();

			if (pid < 0)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				char *argv[2];

				argv[0] = full_path;
				argv[1] = NULL;

				execve(full_path, argv, environ);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(pid, &status, 0);
				free(path_copy);
				if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
				{
					return;
				}
			}
		}

		dir = strtok(NULL, ":");
	}

	printf("Command not found\n");
}
