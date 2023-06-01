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
	ssize_t buf_len = 0;
	int read_len = 0;;

	if (*buf == NULL || *n == 0)
	{
		*buf = malloc(BUFSIZE);
		if (!buf)
			return (-1);
		*n = BUFSIZE;
	}
	while (read_len = read(fd, *buf + buf_len, 1))
	{
		bytes_read += read_len;
		buf_len++;
		if (buf_len >= *n) 
		{
			char *new_buf = realloc(*buf, *n * 2); /* write yoir realloc */
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
}
/**
 * parse_input - tokenizes a string
 * @user_input: string
 * Return: tokenized string
 */
char **parse_input(char *user_input)
{
	char **user_input_array = NULL, *start_to_write = user_input;
	int i = 0, j, len, flag = 0;

	user_input_array = malloc(sizeof(char *) * (num_words(user_input) + 1));
	if (!user_input_array)
		return (0);
	while (*start_to_write)
	{ 
		start_to_write = skip_spaces(start_to_write);
		if (*start_to_write == '\0' || *start_to_write == '#')
			break;
		len = wordlen(start_to_write);
		if (*start_to_write == '$' && *(start_to_write + 1))
		{
			flag = 1;
			user_input_array[i] = malloc(expand(*start_to_write));
		}
		else
			user_input_array[i] = malloc(len + 1);
		if (!user_input_array[i])
		{
			for (j = i; j > 0; j--)
				free(user_input_array[j]);
			free(user_input_array);
			return (0);
		}
		if (!flag)
			_strcpyp(user_input_array[i], start_to_write);
		else
			var_copy(user_input_array[i], *start_to_write);
		start_to_write += len;
		i++;
	}
	user_input_array[i] = NULL;
	return (user_input_array);
}
/**
 * interpret - interprets a command by finding and prepending its path if necessary
 * also handles expansion of special variables
 * @parsed_input: array of arguments to be executed
 * Return: interpreted command
 */
char **interpret(char **parsed_input)
{
	if (!parsed_input || *parsed_input)
		return (NULL);
	if (*(parsed_input[0]) == '/' || == '.')
		expand(parsed_input);
	else

}
