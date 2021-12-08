#include "shell.h"
/**
 * my_gline - Function that reads data from standard input
 * @lineptr: pointer to memory space to store user input
 * @n: variable where the length of the input is stored
 * @stream: define which stream the data will be read from
 *
 * Return: -1 if it fails, len ifi it succeeds
 */
ssize_t my_gline(char **lineptr, size_t *n, FILE *stream)
{
	static size_t s_read;
	size_t r_read;
	char *buffer;
	char letter = 32;
	int rd;

	if (s_read == 0)
		fflush(stream);
	else
		return (-1);
	s_read = 0;
	buffer = malloc(sizeof(char) * MAX_BUFFSIZE);
	if (buffer == NULL)
		return (-1);
	while (letter != 10)
	{
		rd = read(STDIN_FILENO, &letter, 1);
		if (rd == -1 || (rd == 0 && s_read == 0))
		{
			free(buffer);
			return (-1);
		}
		if (rd == 0 && s_read != 0)
		{
			s_read++;
			break;
		}
		if (s_read >= MAX_BUFFSIZE)
			buffer = _realloc(buffer, s_read, s_read + 1);
		buffer[s_read] = letter;
		s_read++;
	}
	buffer[s_read] = '\0';
	if (*lineptr == NULL || *n < s_read)
		*n = (s_read > MAX_BUFFSIZE) ? s_read : MAX_BUFFSIZE;
	*lineptr = _strdup(buffer);
	free(buffer);
	r_read = s_read;
	s_read = (rd != 0) ? 0 : s_read;
	return (r_read);
}
/**
 * my_strtok - function that extracts tokens from strings
 * @buffer: the string to be parsed
 * @delimiter: argument specifies a set of bytes that delimit the
 * tokens in the parsed string
 *
 * Return: a pointer to the next token, or
 * NULL if there are no more tokens.
 */
char *my_strtok(char *buffer, const char *delimiter)
{
	return (strtok(buffer, delimiter));
}
/**
 * my_getenv - function that get an environment variable
 * @key: name of the environment variable
 * @env: value of the environment variable
 * @mood: format for return value
 * 0 -> return value
 * 1 -> return value and key
 *
 * Return: a pointer to the environment variable, or NULL
 * if the variable does not exist
 */
char *my_getenv(char *key, char **env, int mood)
{
	char **tmp_env, *value;
	unsigned int i = 0;

	tmp_env = env;
	while (*tmp_env != NULL)
	{
		value = *tmp_env;
		i = 0;
		while (*(key + i) == *(value + i))
			i++;
		if (i == strlen(key))
		{
			value = (mood == 0) ? (value + i + 1) : value;
			return (value);
		}
		tmp_env++;
	}
	return (NULL);
}
/**
 * my_access -Validate the existence and execution
 * permissions of a file in a given path
 * @band: validate if user input is modified
 * @buffer: pointer to memory space to store modified entry
 * @pmt: pointer to structure with members related to user input
 *
 * Return: 0 it if succeeds, -1 it if fails
 */
int my_access(int *band, char **buffer, st_parameters *pmt)
{
	int r_access = 0, i = 0/*, len = 0*/;
	char *path = my_getenv("PATH", pmt->environment, 0);
	char *tmp_path;
	char **tokens_path = malloc(sizeof(char *) * 50);

	/*info - IMPORT!! duplicate the tree so as not to alter it*/
	tmp_path = _strdup(path);
	for (i = 0; (tokens_path[i] = my_strtok(tmp_path, ":\n")) != NULL; i++)
		tmp_path = NULL;
	/**info - checking the entered path*/
	r_access = access(pmt->tokens[0], X_OK);
	if (r_access == -1)
	{
		for (i = 0; tokens_path[i] != NULL; i++)
		{
			/*info - IMPORT!! forming route in var(buffer)*/
			_concat(buffer, 3, tokens_path[i], "/", pmt->tokens[0]);
			/*info - checking the formed path*/
			r_access = access(*buffer, X_OK);
			if (r_access != -1)
			{
				*band = 1;
				pmt->tokens[0] = *buffer;
				break;
			}
			free(*buffer);
		}
	}

	free(tokens_path[0]);
	free(tokens_path);
	free(tmp_path);
	return (r_access);
}
