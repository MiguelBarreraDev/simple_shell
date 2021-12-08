#include "shell.h"
/**
 * _drealloc - reallocates memory, duplicates
 * the original and adds new elements
 * @src: the original double pointer
 * @size: the size of src
 * @add: quantity of new elements
 * @list: double pointer to a list of new items
 * @mood: 0 -> clone, 1 -> add, 2 -> delete
 *
 * Return: improved double pointer
 */
char **_drealloc(char **src, size_t size, size_t add, char **list, int mood)
{
	char **_new;
	size_t len = 0;
	int i = 0, n_str;

	n_str = (mood == 2) ? (size + add) : (size + add + 1);
	_new = malloc(sizeof(char *) * n_str);
	/* copy and paste */
	if (mood < 3)
	{
		while (*src)
		{
			len = 0;
			if (mood == 2 && *src == *list)
			{
				src++;
				continue;
			}
			len = strlen(*src) + 1;
			_new[i] = malloc(sizeof(char) * len);
			strcpy(_new[i], *src);
			i++;
			src++;
		}
	}
	/* additional elements */
	if (mood == 1)
	{
		while (add)
		{
			len = strlen(*list) + 1;
			_new[i] = malloc(sizeof(char) * len);
			strcpy(_new[i], *list);
			i++;
			list++;
			add--;
		}
	}
	_new[i] = NULL;
	return (_new);
}
/**
 * _dstrlen - function to get the number of elements of a double pointer
 * @ptr: Variable that refers to the double pointer
 *
 * Return: number of elements
 */
unsigned int _dstrlen(char **ptr)
{
	unsigned int len = 0;

	while (*(ptr + len) != NULL)
		len++;

	return (len);
}
/**
 * _concat - function to concatenate strings
 * @buff: reference to the memory where the result is stored
 * @n: string number to concatenate
 * @...: Referencia a argumentos variadic
 */
void _concat(char **buff, int n, ...)
{
	char *save = NULL;
	char **arr;
	int pos = 0, len = 0;
	va_list ptr;

	va_start(ptr, n);
	/* info - IMPORT!! allocate memory */
	arr = malloc(sizeof(char *) * n);
	while (pos < n)
	{
		*(arr + pos) = va_arg(ptr, char *);
		save = *(arr + pos);
		len += strlen(save);
		pos++;
	}

	/* info - IMPORT!! allocate memory */
	*buff = malloc(sizeof(char) * (len + 1));
	strcpy(*buff, "");
	for (pos = 0; pos < n; pos++)
		strcat(*buff, *(arr + pos));

	free(arr);
	va_end(ptr);
}
/**
 * to_str - convert int to string
 * @n: number to be converted into a string
 * Return: pointer to a new string
 */
char *to_str(int n)
{
	char *str, *p;
	int n2 = n, i = 0;

	while (n2 > 0)
	{
		i++;
		n2 /= 10;
	}
	str = malloc(sizeof(char) * (i + 1));
	str[i] = '\0';

	p = &str[i];
	p--;
	while (n > 0)
	{
		*p = n % 10 + '0';
		n /= 10;
		p--;
	}
	return (str);
}
