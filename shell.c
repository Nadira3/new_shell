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
