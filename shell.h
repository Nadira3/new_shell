#ifndef SHELL_H
#define SHELL_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#define BUFSIZE 120


extern char **environ;
typedef struct var
{
	char *str;
	char (*func_ptr)(char **arg);
} var_func;
char *read_input(ssize_t *, int);
int _getline(char **, size_t *, int);
void print_prompt(int, int);
int _putchar(char);
int _puts(char *);
char **parse_input(char *);
char *_strtok(char *, char *);
char *_strcpy(char *, char *);
int _strlen(char *);
char *_strdup(char *);
int num_words(char *);
char (*interpret_func(char *))(char **);
int _strcmp(char *, char *);
char *_getenv(char *);
char *skip_spaces(char *);
int wordlen(char *);
char *_strcpyp(char *, char *);
char *_strcat(char *, char *);
char *interpret(char **, int);
char *input_expand(char *, int);
char *path(char *);
int execute(char *, char **, int *, char **);
void free_func(char *, char **, char *);
#endif

