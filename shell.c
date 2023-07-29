#include "shell.h"

/**
 * display_prompt - displays the prompt
 * @prompt: pointer to a character
 */
void display_prompt(const char *prompt)
{
	write(STDOUT_FILENO, prompt, strlen(prompt));
}

/**
 * read_input - reads the input using the getline function
 * @bufsize: function parameter
 * Return: input command
 */
char *read_input(size_t *bufsize)
{
	char *command = NULL;
	ssize_t cmdread = getline(&command, bufsize, stdin);

	if (cmdread == -1)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(command);
		return (NULL);
	}
	command[strcspn(command, "\n")] = '\0';
	return (command);
}

/**
 * parse_exec_command - parse and execute input command
 * @command: input command
 */
void parse_exec_command(char *command)
{
	char *argv[MAX_ARGS];
	char *commands[MAX_COMMANDS];
	int a, exit_status, num_commands, argc;

	if (command[0] == '#')
		return;
	num_commands = commands_separator(command, commands);
	for (a = 0; a < num_commands; a++)
	{	argc = parse_func(commands[a], argv);
		if (_strcmp(argv[0], "exit") == 0)
		{
			if (argc >= 2)
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
			env_func();
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
 * ignore_ctrl_c - ingore Ctrl + C
 * @signum: function parameter
 */
void ignore_ctrl_c(int signum)
{
	(void)signum;
}

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0
 */
int main(int ac, char *av[])
{
	const char *prompt = "(myShell)$ ";
	char *command = NULL;
	size_t bufsize = BUFF_SIZE;
	int interactive = isatty(fileno(stdin));

	signal(SIGINT, ignore_ctrl_c);
	if (ac > 1)
	{
		FILE *script_file = fopen(av[1], "r");

		if (script_file == NULL)
		{
			fprintf(stderr, "%s: Can't open %s\n", av[0], av[1]);
			exit(EXIT_FAILURE);
		}
		else
		{
			run_script(script_file);
			fclose(script_file);
		}
	}
	else
	{
		while (1)
		{
			if (interactive)
			{
				display_prompt(prompt);
			}

			command = read_input(&bufsize);

			if (command == NULL)
				break;

			parse_exec_command(command);
			free(command);
		}
	}
	return (0);
}
