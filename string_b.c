#include "shell.h"
/**
 * num_words - finds the number of words in a string
 * @str: string
 * Return: number of words counted
 */
int num_words(char *str)
{
	int n = 0;
	char *ptr;

	if (!str)
		return (n);
	ptr = str;
	while (*ptr)
	{
		while (*ptr && *ptr == ' ')
			ptr++;
		if (*ptr && (*(ptr + 1) == ' ' || !(*(ptr + 1))))
			n++;
		ptr++;
	}
	return (n);
}
/**
 * skip_spaces - skips spaces
 * @str: string argument
 * Return: pointer to next character in the string
 */
char *skip_spaces(char *str)
{
	if (str)
	{
		while (*str)
		{
			if (*str != ' ')
				break;
			str++;
		}
	}
	return (str);
}
/**
 * wordlen - finds the lengthbof a word in a string
 * @str: string
 * Return: the length of a word
 */
int wordlen(char *str)
{
	if (*str == ' ' || !*str)
		return (0);
	return (1 + wordlen(str + 1));
}
/**
 * _strcpyp - copies a word to a buffer
 * @str1: buffer
 * @str2: word pointer
 * Return: buffer
 */
char *_strcpyp(char *str1, char *str2)
{
	char *ptr1 = str1, *ptr2 = str2;

	if (!ptr1 || !ptr2)
		return (str1);
	while (*ptr2 && *ptr2 != ' ')
	{
		*ptr1 = *ptr2;
		ptr1++;
		ptr2++;
	}
	*ptr1 = '\0';
	return (str1);
}
/**
 * _strcat - concatenates a string
 * @str1: first string
 * @str2: second string
 * Return: str1
 */
char *_strcat(char *str1, char *str2)
{
	char *ptr1 = str1, *ptr2 = str2;

	if (!ptr2 || !ptr1)
		return (str1);
	while (*ptr1)
		ptr1++;
	_strcpyp(ptr1, ptr2);
	return (str1);
}
