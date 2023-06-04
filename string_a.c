#include "shell.h"
/**
 * _strdup - duplicates a string
 * @str: string to be duplicated
 * Return: duplicated copy of str
 */
char *_strdup(char *str)
{
	char *new_str;
	int str_len;

	if (!str)
		return (NULL);
	str_len = _strlen(str);
	new_str = malloc(str_len + 1);
	if (!new_str)
		return (NULL);
	_strcpy(new_str, str);
	return (new_str);
}
/**
 * _strlen - finds the length of a string
 * @str: string
 * Return: length of the string
 */
int _strlen(char *str)
{
	if (!*str)
		return (0);
	return (1 + _strlen(str + 1));
}
/**
 * _strcpy - copies the content of one string to another
 * @str1: new string
 * @str2: old string
 * Return: new string
 */
char *_strcpy(char *str1, char *str2)
{
	char *ptr1, *ptr2;

	if (!str1 || !str2)
		return (NULL);
	ptr1 = str1;
	ptr2 = str2;
	while (*ptr2)
	{
		*ptr1 = *ptr2;
		ptr1++;
		ptr2++;
	}
	*ptr1 = '\0';
	return (str1);

}
/**
 * _strtok - tokenizes a string
 * @str: string to be separated
 * @delimiter: list of characters used to separate strings
 * Return: pointer to tokenized string
 */
char *_strtok(char *str, char *delim)
{
	static char *ptr = NULL;
	int i, j;
	int str_len, delim_len;
	int found_delim = 0;

	if (str != NULL) 
		ptr = str;
	else
	{
		if (ptr == NULL)
			return NULL;
		str = ptr;
	}
	str_len = _strlen(str);
	delim_len = _strlen(delim);

	for (i = 0; i < str_len; i++)
	{
		for (j = 0; j < delim_len; j++)
		{
			if (str[i] == delim[j])
			{
				str[i] = '\0';
				found_delim = 1;
				break;
			}
		}
		if (found_delim) 
		{
			found_delim = 0;
			break;
		}
	}

	ptr = (i < str_len) ? &str[i + 1] : NULL;
	return str;
}
/**
 * _strcmp - compares to string to check if they are an exact match
 * @str1: first string
 * @str2: second string
 * Return: 1 if strings match, otherwise 0
 */
int _strcmp(char *str1, char *str2)
{
	char *ptr1 = str1, *ptr2 = str2;

	if (!ptr1 || !ptr2)
		return (0);
	while (*ptr1 || *ptr2)
	{
		if (*ptr2 != *ptr1)
			return (0);
		ptr1++;
		ptr2++;
	}
	return (1);
}
