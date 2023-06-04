#include "shell.h"
int _puts(char *str)
{
	char *ptr = str;

	if (!ptr)
		return (0);
	while (*ptr)
	{
		_putchar(*ptr);
		ptr++;
	}
	return (1);
}
int _putchar(char c)
{
	int n;

	n = write(1, &c, 1);
	return (n == -1 ? 0 : 1);
}
void print_prompt(int term, int fd)
{
	char *prompt = "$ ";

	if (term && !fd)
		_puts(prompt);
}
