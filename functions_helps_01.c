#include "shell.h"
/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previsouly allocated by malloc
 * @old_size: size of the allocated memory for ptr
 * @new_size: new size of the new memory block
 *
 * Return: pointer to the newly allocated memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *ptr1, *ptr2;
	unsigned int i, j;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr1 = malloc(new_size);

	if (ptr1 == NULL)
		return (NULL);

	ptr2 = ptr;
	if (new_size > old_size)
		j = old_size;
	if (new_size < old_size)
		j = new_size;

	for (i = 0; i < j; i++)
		ptr1[i] = ptr2[i];

	free(ptr);
	return (ptr1);
}
/**
 * _atoi - converts a string to an integer
 * @s: string to be converted
 *
 * Return: the int converted from the string
 */
int _atoi(char *s)
{
	int i = 0, d = 0, n = 0, x = 0, f = 0, digit = 0;

	while (s[x] != 0)
		x++;

	while (i < x && f == 0)
	{
		if (s[i] == '-')
			++d, i++;
		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (d % 2)
				digit = -digit;
			n = n * 10 + digit;
			f = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			f = 0;
		}
		i++;
	}
	if (f == 0)
		return (0);
	return (n);
}
/**
 * _strdup - function that duplicates a string
 * @buffer: the string to be duplicated
 *
 * Return: pointer to string that was duplicated
 */
char *_strdup(char *buffer)
{
	unsigned int len = 0;
	char *new_buffer;

	len = strlen(buffer);
	new_buffer = malloc(sizeof(char) * (len + 1));

	strcpy(new_buffer, buffer);

	return (new_buffer);
}
/**
 * _trim - function that removes whitespace at the beginning
 * @str: double pointer to string to format
 */
void _trim(char **str)
{
	int i = 0, j = 0, len = 0;
	char *tmp = *str;
	char *fstr = NULL;

	if (**str == ' ' || **str == '\t')
	{
		while ((*(*str + i) == ' ' || *(*str + i) == '\t') && *(*str + i) != '\0')
			i++;
		while (*(*str + i + len) != '\0')
			len++;
		fstr = malloc(sizeof(char) * len + 1);
		while (*(*str + i) != '\0')
		{
			*(fstr + j) = *(*str + i);
			i++;
			j++;
		}
		*(fstr + j) = '\0';
		*str = fstr;
		free(tmp);
	}
}
/**
 * _free - function to free memory allocated to a double pointer
 * @ptr: double pointer pointing to memory space to free
 */
void _free(char **ptr)
{
	int pos = 0;

	while (*(ptr + pos))
	{
		free(*(ptr + pos));
		pos++;
	}
	free(ptr);
}
