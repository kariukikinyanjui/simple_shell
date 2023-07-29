#include "shell.h"

/**
 * get_full_path - a fuction that gets the full path
 * @dir: function parameter 1
 * @command: function parameter 2
 * @full_path: function parameter 3
 */
void get_full_path(char *dir, const char *command, char full_path[])
{
	strncpy(full_path, dir, BUFF_SIZE - 1);
	full_path[BUFF_SIZE - 1] = '\0';
	_strcat(full_path, "/");
	_strcat(full_path, command);
}

/**
 * exec_command_path - handles the actual execution of the command
 * @full_path: function parameter 1
 * @argv: array pointer to a character
 * Return: Nothing
 */
void exec_command_path(char *full_path, char *argv[])
{
	int status;
	pid_t pid = fork();

	if (pid < 0)
	{
		fprintf(stderr, "%s: Error creating child process\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(full_path, argv, environ);
		fprintf(stderr, "%s: %d: %s: not found\n", argv[0], errno, argv[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			return;
		}
	}
}

/**
 * find_exec_command - function is responsible for traversing the PATH
 * environment variable and finding the full path of the executable
 * @argv: pointer to a string
 */
void find_exec_command(char *argv[])
{
	char *path = _getenv("PATH");
	char *path_copy = NULL;
	char *dir = NULL;
	char full_path[BUFF_SIZE];

	if (path == NULL)
	{
		fprintf(stderr, "%s: PATH environment variable notfound\n", argv[0]);
		return;
	}
	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		fprintf(stderr, "%s: strdup failed\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	dir = my_strtok(path_copy, ":");
	while (dir != NULL)
	{
		if (argv[0][0] == '/')
		{
			if (access(argv[0], F_OK) == 0)
			{
				exec_command_path(argv[0], argv);
				free(path_copy);
				return;
			}
			break;
		}
		get_full_path(dir, argv[0], full_path);

		if (access(full_path, F_OK) == 0)
		{	exec_command_path(full_path, argv);
			free(path_copy);
			return;
		}
		dir = my_strtok(NULL, ":");
	}
	free(path_copy);
	write(STDOUT_FILENO, "No such file or directory\n", 26);
}

/**
 * file_path -simple wrapper around the core functionality provided
 * by find_exec_command
 * @argv: pointer to an array
 */
void file_path(char *argv[])
{
	find_exec_command(argv);
}

/**
 * run_script -handles the non-interactive mode of the shell
 * @file_stream: name of the script file to execute
 */
void run_script(FILE *file_stream)
{
	char *line = NULL;
	size_t  bufsize = 0;
	ssize_t line_len;

	while ((line_len = getline(&line, &bufsize, file_stream)) != -1)
	{
		line[strcspn(line, "\n")] = '\0';

		parse_exec_command(line);
	}
	free(line);
}
