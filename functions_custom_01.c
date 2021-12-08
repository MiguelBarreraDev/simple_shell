#include  "shell.h"
/**
 * shell_env - show all environment variables
 * @pmt: pointer to structure with members related to user input
 */
void shell_env(st_parameters *pmt)
{
	unsigned int i;

	for (i = 0; (pmt->environment[i]) != NULL; i++)
		printf("%s\n", pmt->environment[i]);
}
/**
 * shell_setenv - add and/or modify environment variables
 * @pmt: pointer to structure with members related to user input
 */
void shell_setenv(st_parameters *pmt)
{
	char **env = pmt->environment;
	char **new_env;
	char *new_variable;
	char *key = pmt->tokens[1];
	char *value = pmt->tokens[2];
	char *current = NULL;
	size_t  len_env = 0;

	len_env = _dstrlen(env);

	/*----------------- if exists variable --------------*/
	current = my_getenv(key, env, 1);
	if (current != NULL)
	{
		new_env = _drealloc(env, len_env, 0, &current, 2);
		/* info - Free memory for old env assigned */
		if (pmt->band == 1)
			_free(env);
		/* info - New env assigned */
		pmt->environment = new_env;
		pmt->band = 1;

		env = pmt->environment;
	}

	/*---------- Start - New variable ---------*/
	/* info - IMPORT!! allocate memory */
	_concat(&new_variable, 3, key, "=", value);

	/*----------- Start - Modify environment ---------*/
	len_env = _dstrlen(env);
	new_env = _drealloc(env, len_env, 1, &new_variable, 1);
	free(new_variable);
	/* info - Free memory for old env assigned */
	if (pmt->band == 1)
		_free(env);
	/* info - New env assigned */
	pmt->environment = new_env;
	pmt->band = 1;
}

/**
 * shell_unsetenv - remove environment variables
 * @pmt: pointer to structure with members related to user input
 */
void shell_unsetenv(st_parameters *pmt)
{
	char **new_env;
	char **env = pmt->environment;
	char *key = pmt->tokens[1];
	char *address = my_getenv(key, env, 1);
	size_t len_env = 0;
	char *message = "ERROR: Not exist the environment variable\n";

	if (!address)
		write(STDERR_FILENO, message, strlen(message));
	else
	{
		len_env = _dstrlen(env);
		new_env = _drealloc(env, len_env, 0, &address, 2);

		/* free memory for old env assigned */
		if (pmt->band == 1)
			_free(env);
		/* New env assigned */
		pmt->environment = new_env;
		pmt->band = 1;
	}
}
/**
 * shell_clear - clean the terminal
 * @pmt: pointer to structure with members related to user input
 */
void shell_clear(__attribute__((unused))st_parameters *pmt)
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
/**
 * shell_exit - causes normal termination of the process
 * @pmt: pointer to structure with members related to user input
 */
void shell_exit(st_parameters *pmt)
{
	char *str_status = NULL;
	int status;

	str_status = pmt->tokens[1];
	status = (!str_status) ? 0 : atoi(str_status);

	(void)status;
	free(pmt->command);
	free(pmt->tokens[0]);
	free(pmt->tokens);
	if (pmt->band == 1)
		_free(pmt->environment);
	exit(0);
}
