#include "shell.h"
/**
 * _getenv - gets the value of an environment variable using its key
 * @key: key of environment variable
 * Return: pointer to value of key
 */
char* _getenv(char* key) 
{
	char *var_name, *value;
	int i, j, key_len, value_len, k = 0;

	if (key == NULL)
		return NULL;

	for (i = 0; environ[i] != NULL; i++) 
	{
		key_len = strlen(key);
		var_name = malloc(key_len + 1);
	/* a strncmp works better here but i forgot, cant rewrite, lol */
		if (!var_name)
			return (0);
		for (j = 0; j < key_len; j++)
			var_name[j] = environ[i][j];
		var_name[j++] = '\0';
		if (var_name != NULL && _strcmp(var_name, key) == 1)
		{
			value_len = strlen(environ[i]);
			value = malloc(value_len + 1);
			if (!value)
				return (0);
			while (j <= value_len)
				value[k++] = environ[i][j++];
			value[k] = '\0';
			free(var_name);
			return (value);
		}
		free(var_name);
	}
	return (NULL);
}
char *path(char *command)
{
	char *filepath = _getenv("PATH"), *env_path = NULL;
	char *path_copy = _strdup(filepath), *token = _strtok(path_copy, ":");
	size_t env_path_len;

	while (token != NULL)
	{
		env_path_len = _strlen(token) + _strlen(command) + 2;
		env_path = malloc(env_path_len);
		if (env_path == NULL)
		{
			free(filepath);
			free(path_copy);
			return (NULL);
		}
		_strcpy(env_path, token);
		_strcat(env_path, "/");
		_strcat(env_path, command);
		if (access(env_path, X_OK) == 0)
		{
			free(filepath);
			free(path_copy);
			return (env_path);
		}
		free(env_path);
		env_path = NULL;
		token = _strtok(NULL, ":");
	}
	free(path_copy);
	free(filepath);
	return (env_path);
}

void free_func(char *a, char **c, char *b)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
	{
		int i;
		for (i = 0; c[i]; i++)
			free(c[i]);
		free(c);
	}
}
