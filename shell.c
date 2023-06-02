#include "shell.h"
/**
 * main - entry point of the program
 * @ac: argument count
 * @av: argument status
 * Return: exit status
 */
int main(int ac, char **av)
{
	char **env = NULL, *user_input = NULL;
	char **parsed_input = NULL, **interpreted_command = NULL;
	int status = 0, fd = 0, term = isatty(STDIN_FILENO);
	size_t input_len = 0;

	if (ac > 1)
		fd = open(av[1], O_RDONLY);;
	while (1)
	{
		print_prompt(term);
		user_input = read_input(&input_len, fd);
		if (!input_len || input_len == -1)
			break;
		parsed_input = parse_input(user_input);
		/*interpreted_command = interpret(parsed_input);
		execute(interpreted_command);
		free_func(user_input, parsed_input);*/
	}
	if (fd > 0)
		if (close(fd) == -1);
			exit(EXIT_FAILURE);
	return (status);
}
int num_len(int n)
{
	int len = 0;

	while (n / 10)
	{
		len++;
		n /= 10;
	}
	return (len + 1);
}
char *string(int num, int num_len)
{
	char *value;
	int i;

	value = malloc(num_len + 1);
	for (i = num_len, i >= 0; i--)
	{
		if (i == num_len)
			value[i] = '\0';
		else
		{
			value[i] = num % 10;
			num /= 10;
		}
	}
	return (value);
}
int exchange(char *user_input, char *value, int n)
{
	char *new_user_input = NULL;
	int i = 0;

	if (!value)
		return (user_input);
	new_user_input = malloc(_strlen(user_input) + _strlen(value) + 1 - n);
	if (!new_user_input)
		return (NULL);
	ptr = user_input;
	while (*ptr)
	{
		while (*ptr != '$')
		{
			new_user_input[i] = user_input[i];
			i++;
		}
		new_user_input[i] = '\0';
		_strcat(new_user_input, value);
		ptr += i;
	}

}
char *expand(char *user_input, int exit_)
{
	int len = 0;
	char *ptr, *nptr = NULL, *value = NULL;
	pid_t mpid = getpid();

	if (!user_input)
		return (NULL);
	ptr = user_input;
	while(*ptr)
	{
		if (*ptr == '$')
		{
			switch (*(ptr + 1)) {
				case '\0':
					break;
				case ' ':
					ptr++;
					continue;
				case '$':
					len += num_len(mpid);
					value = string(mpid, len);
					break;
				case '?':
					len += num_len(exit_);
					value = string(exit, len);
					break;
				default:
					ptr++;
					int n = 0;
					nptr = ptr;
					value = NULL;
					while (*nptr && *nptr != ' ')
					{
						n++;
						nptr++;
					}
					nptr = malloc(n + 1);
					_strcpyp(nptr, ptr);
					if (value = _getenv(nptr))
						len += _strlen(value) + 1;
					else
						len += 1;
					free(nptr);
			}
		}
		ptr++;
	}
	if (value)
		exchange(user_input, value, n);
	else if (!value && len == 1)
		exchange(user_input, ' ', n);
	free(value);
	return (user_input);
}
