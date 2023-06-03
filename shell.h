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
char *read_input(ssize_t *input_len, int fd);
int _getline(char **buf, size_t *n, int fd);
void print_prompt(int term);
int _putchar(char c);
int _puts(char *str);
char **parse_input(char *user_input);
char *_strtok(char *str, char *delim);
char *_strcpy(char *str1, char *str2);
int _strlen(char *str);
char *_strdup(char *str);
int num_words(char *str);
char *skip_spaces(char *str);
int wordlen(char *str);
char *_strcpyp(char *str1, char *str2);
char *_strcat(char *str1, char *str2);
char **interpret(char **parsed_input);
char *expand_and_sub(char *input, char *var_name);
char *input_expand(char *user_input);
#endif

