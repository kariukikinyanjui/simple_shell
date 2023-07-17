#ifndef SHELL_H
#define SHELL_H
#define BUFF_SIZE 1024
#define MAX_ARGS 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void parse_func(char *command, char *argv[]);
extern char **environ;
void file_path(char *argv[]);
void exit_func(char *argv[]);
void env_func(char *argv[]);
char *my_strtok(char *str, const char *delim);

#endif
