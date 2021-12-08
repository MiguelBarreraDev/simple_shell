#include "shell.h"
#include <linux/limits.h>
#include <limits.h>
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
 * change_path - update PWD and OLDPWD environment variables
 * @pmt: pointer to structure with members related to user input
 * @pwd: array containing the new value of the environment variable PWD
 * @old: array containing the new value of the environment variable OLDPWD
 */
void change_path(st_parameters *pmt, char pwd[PATH_MAX], char old[PATH_MAX])
{
	char *message = "No such file or directory\n";

	if (chdir(pwd) == -1)
		write(STDERR_FILENO, message, strlen(message));
	else
	{
		pmt->tokens[1] = "PWD";
		pmt->tokens[2] = pwd;
		shell_setenv(pmt);
		pmt->tokens[1] = "OLDPWD";
		pmt->tokens[2] = old;
		shell_setenv(pmt);
	}
}
/**
 * shell_cd - función que cambia el directorio de trabajo actual
 * @pmt: pointer to structure with members related to user input
 */
void shell_cd(st_parameters *pmt)
{
	char path_dest[PATH_MAX] = "", path_old[PATH_MAX] = "", *save;

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
		if (*(pmt->tokens[1]) != '/')
			getcwd(path_dest, sizeof(path_dest));
		strcat(path_dest, "/");
		strcat(path_dest, pmt->tokens[1]);
		if (path_dest[0] != '\0')
			change_path(pmt, path_dest, path_old);
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
