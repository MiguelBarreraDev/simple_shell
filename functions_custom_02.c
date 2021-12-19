#include "shell.h"
/**
 * shell_signal - function that controls program interruption
 * @sig: integer number
 */
void shell_signal(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n:) ", 4);
}
/**
 * shell_cd - función que cambia el directorio de trabajo actual
 * @pmt: pointer to structure with members related to user input
 */
void shell_cd(st_parameters *pmt)
{
	char path_old[PATH_MAX] = "", *save, path_dest[PATH_MAX] = "";

	getcwd(path_old, sizeof(path_old));
	/* info - search path home in environment */
	if (pmt->tokens[1] == NULL || *(pmt->tokens[1]) == '~')
	{
		save = my_getenv("HOME", pmt->environment, 0);
		strcpy(path_dest, save);
		if (save != NULL)
			change_path(pmt, path_dest, path_old);
	}
	else if (*(pmt->tokens[1]) == '-')
	{
		save = my_getenv("OLDPWD", pmt->environment, 0);
		strcpy(path_dest, save);
		if (save != NULL)
			change_path(pmt, path_dest, path_old);
	}
	else
	{
		shell_cd_arg(pmt, path_dest, path_old);
	}
}
/**
 * shell_printenv - function that returns a variable specified as a parameter
 * @pmt: pointer to structure with members related to user input
 */
void shell_printenv(st_parameters *pmt)
{
	char *key = pmt->tokens[1];
	char *var = my_getenv(key, pmt->environment, 1);

	write(1, var, strlen(var));
}
