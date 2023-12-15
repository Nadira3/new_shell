#include "shell.h"
/**
 * read_input - reads a line of input from a file stream
 * Return: an array of input from the file stream
 * delimited by a newline character
 */
char *read_input(ssize_t *input_len, int fd)
{
	char *buf = NULL;
	size_t n = 0;
	ssize_t len = 0;

	len = _getline(&buf, &n, fd);
	/*if (len == -1)
	{
		free(buf);
		exit_status = 2;
		exit(EXIT_FAILURE);
	}*/
	*input_len = len > 0 ? len : 0;
	return (len == -1 ? NULL : buf);
}
/**
 * _getline - gets a line of input from a file stream
 * @buf: stores input in this memory space
 * @n: size of space allocated for input
 * @fd: file descriptor of file read
 * Return: number of bytes read
 */
int _getline(char **buf, size_t *n, int fd)
{
	ssize_t bytes_read = 0;
	size_t buf_len = 0;
	int read_len = 0;;

	if (*buf == NULL || *n == 0)
	{
		*buf = malloc(BUFSIZE);
		if (!buf)
			return (-1);
		*n = BUFSIZE;
	}
	while ((read_len = read(fd, *buf + buf_len, 1)))
	{
		bytes_read += read_len;
		buf_len++;
		if (buf_len >= *n) 
		{
			char *new_buf = realloc(*buf, *n * 2); /* write your realloc */
			if (new_buf == NULL)
				return (-1);
			*buf = new_buf;
			*n *= 2;
		}
		if ((*buf)[buf_len - 1] == '\n') 
		{
			(*buf)[buf_len - 1] = '\0';
			break;
		}
	}
	if (read_len == -1 || (!read_len && !bytes_read))
		return (-1);
	return (1);
}
/**
 * parse_input - tokenizes a string
 * @user_input: string
 * Return: tokenized string
 */
char **parse_input(char *user_input)
{
	char **user_input_array = NULL, *start_to_write = user_input;
	int i = 0, j, len;

	user_input_array = malloc(sizeof(char *) * (num_words(user_input) + 1));
	if (!user_input_array)
		return (0);
	while (*start_to_write)
	{ 
		start_to_write = skip_spaces(start_to_write);
		if (*start_to_write == '\0' || *start_to_write == '#')
			break;
		len = wordlen(start_to_write);
		user_input_array[i] = malloc(len + 1);
		if (!user_input_array[i])
		{
			for (j = i; j > 0; j--)
				free(user_input_array[j]);
			free(user_input_array);
			return (0);
		}
		_strcpyp(user_input_array[i], start_to_write);
		start_to_write += len;
		i++;
	}
	user_input_array[i] = NULL;
	return (user_input_array);
}
/**
 * interpret_func - interpretes the tokenized string by separating into
 * command and arguments and finding its corresponding path and/or 
 * executable if it exists
 * @arg_command: array of command-line input in tokenized form
 * Return: pointer to built-in function if present or NULL
 */
char (*interpret_func(char *arg_command))(char **arg)
{
	var_func interpreted_command[] = {
		/*{"env", tenv_func},
		{"setenv", setenv_func},
		{"unsetenv", unsetenv_func},*/
		{NULL, NULL}
	};
	int i = 0;

	while (interpreted_command[i].str)
	{
		if ((_strcmp(arg_command, interpreted_command[i].str)))
			return (interpreted_command[i].func_ptr);
		i++;
	}
	return (interpreted_command[i].func_ptr);
}
void exit_func(int status)
{
	return;
}
char *interpret(char **arg, int exit_status)
{
	char *filepath = NULL, *command = NULL;

	if (!arg || !*arg)
		return (0);
	command = arg[0];
	if (*command == '/' || *command == '.')
		filepath = access(command, F_OK | X_OK) != 0 ? NULL : _strdup(command);
	else
		filepath = path(command);
	/* check if they are executable */
	if (!filepath)
	{
		_puts(arg[0]);
		_puts(": command not found\n");
		return (0);
	}
	if (access(filepath, F_OK | X_OK) != 0 && !(interpret_func(command)))
	{
		perror(command);
		exit_status = EXIT_FAILURE;
		exit_func(exit_status);
	}
	return (filepath);
}
