#include "shell.h"
#include <ctype.h>
int num_len(int n)
{
	int len = 0;

	while (n / 10)
	{
		len++;
		n /= 10;
	}
	return len + 1;
}

char *string(int num, int num_len)
{
	char *value;
	int i;

	value = malloc(num_len + 1);
	if (!value)
		return (0);
	value[num_len] = '\0';
	for (i = num_len - 1; i >= 0; i--)
	{
		value[i] = num % 10 + '0';
		num /= 10;
	}
	return value;
}
char *var_name_extract(char *input)
{
	char *var_name = NULL;
	char *ptr = input;
	int post = 0;
	int i = 0;

	if (!input)
		return (0);
	var_name = malloc(_strlen(input) * 2);
	while (*ptr)
	{
		if (*ptr == '$')
		{
			ptr++;
			if (!*ptr)
				return (0);
			while (isalnum(*ptr) || *ptr == '$' || *ptr == '?')
			{
				var_name[i] = *ptr;
				ptr++;
				i++;
			}
			var_name[i] = '\0';
			_strcat(var_name, "/");
			_strcat(var_name, string(post, num_len(post)));
			_strcat(var_name, ":");
			i += (2 + num_len(post));
		}
		post++;
		ptr++;
	}
	if (!i)
		free(var_name);
	return (i ? var_name : NULL);
}
char *lookup_variable(char *var_name, int exit_status)
{
	char *value = NULL, *token = NULL, *var_copy = NULL;
	pid_t mpid;

	var_copy = strdup(var_name);
	if (var_copy == NULL)
		return (NULL);

	token = strtok(var_copy, "/");
	if (token == NULL)
	{
		free(var_copy);
		return (NULL);
	}
	switch (*var_name)
	{
		case '$':
			mpid = getpid();
			value = string(mpid, num_len((int)mpid));
			break;
		case '?':
			value = string(exit_status, num_len(exit_status));
			break;
		default:
			value = _getenv(token);
	}
	free(var_copy);
	return (value);
}
char *expand_and_sub(char *input, char *var_name, int exit_status)
{
	char *name_copy = NULL, *new_input = NULL, *value = NULL;
	int i = 0;

	if (!var_name)
		return input;

	new_input = malloc(BUFSIZ);
	name_copy = _strtok(var_name, "/:");
	while (input[i] != '$')
	{
		new_input[i] = input[i];
		i++;
	}
	new_input[i] = '\0';
	while (name_copy != NULL)
	{
		while (input[i] != '$' && input[i] != *var_name)
		{
			new_input[i] = input[i];
			i++;
		}
		new_input[i] = '\0';
		value = lookup_variable(name_copy, exit_status);
		name_copy = _strtok(NULL, "/:");
		if (name_copy == NULL)
			break;
		if (value)
		{
			int j = 0;
			while (value[j])
				new_input[i++] = value[j++];
			new_input[i] = '\0';
		}
	}
	/*if (!value)
		putchar(10);
	free(value);
	free(input);*/
	return (new_input);
}
char *input_expand(char *user_input, int exit_status)
{
	char *var_name;

	if (!user_input)
		return (0);
	var_name = var_name_extract(user_input);
	user_input = expand_and_sub(user_input, var_name, exit_status);
	free(var_name);
	return (user_input);
}
/*
void test_expand_and_sub(char *input)
{
	char *var_name = var_name_extract(input);
	printf("Input: %s\n", var_name);
	char *expanded = expand_and_sub(input, var_name);

	printf("Input: %s\n", input);
	printf("Expanded: %s\n", expanded);
	printf("-------------------------\n");

	free(var_name);
	if (expanded != input)
		free(expanded);
}

int main()
{
	// Test cases
	test_expand_and_sub("Hello $HOME!");
	test_expand_and_sub("This is a $TEST.");
	test_expand_and_sub("echo $$.");
	test_expand_and_sub("echo $");
	test_expand_and_sub("echo $?");
	test_expand_and_sub("No variable here.");
	test_expand_and_sub("Multiple $VARIABLES $TO $EXPAND.");

	return 0;
}
*/
