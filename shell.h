#ifndef SHELL_H
#define SHELL_H
#define BUFF_SIZE 1024
#define MAX_ARGS 20
#define MAX_COMMANDS 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

void display_prompt(const char *prompt);
extern char **environ;
void exit_func(int status);
void env_func(void);
char *my_strtok(char *str, const char *delim);
int commands_separator(char *input, char *commands[]);
int _strcmp(const char *str1, const char *str2);
char *_getenv(const char *name);
char *_strcat(char *dest, const char *src);
void _setenv(char *argv[]);
void _unsetenv(char *argv[]);
char *read_input(size_t *bufsize);
void parse_exec_command(char *command);
void get_full_path(char *dir, const char *command, char full_path[]);
void find_exec_command(char *argv[]);
void file_path(char *argv[]);
void exec_command_path(char *full_path, char *argv[]);
int parse_func(char *command, char *argv[]);
void ignore_ctrl_c(int signum);
void run_script(FILE *file_stream);
void execute_commands(char *commands[], int num_commands);
char *_getline(void);
#endif
