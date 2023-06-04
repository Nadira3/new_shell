#include "shell.h"
/**
 * main - entry point of the program
 * @ac: argument count
 * @av: argument status
 * Return: exit status
 */
int main(int ac, char **av)
{
	char **env = { NULL }, *user_input = NULL;
	char **parsed_input = NULL, *interpreted_command = NULL;
	int fd = 0, term = isatty(STDIN_FILENO), exit_status = 0;
	ssize_t input_len = 0;

	if (ac > 1)
		fd = open(av[1], O_RDONLY);
	while (1)
	{
		print_prompt(term, fd);
		user_input = read_input(&input_len, fd);
		if (!input_len || input_len == -1)
			break;
		user_input = input_expand(user_input, exit_status);
		parsed_input = parse_input(user_input);
		interpreted_command = interpret(parsed_input, exit_status);
		execute(interpreted_command, parsed_input, &exit_status, env);
		free_func(user_input, parsed_input, interpreted_command);
	}
	if (fd > 0)
		if (close(fd) == -1)
			exit_status = EXIT_FAILURE;
	return (exit_status);
}
