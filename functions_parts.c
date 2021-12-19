#include "shell.h"
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
 * shell_cd_arg - función que cambia el directorio de trabajo actual
 * @pmt: pointer to structure with members related to user input
 * @path_dest: array containing the new value of the environment variable PWD
 * @path_old: array containing the new value of the environment variable OLDPWD
 */
void shell_cd_arg(st_parameters *pmt, char path_dest[], char path_old[])
{
	ssize_t len = 0;

	if (*(pmt->tokens[1]) != '/')
		getcwd(path_dest, PATH_MAX);
	len = strlen(path_dest) - 1;

	if (strcmp(pmt->tokens[1], "..") == 0)
	{
		for (; len >= 0; len--)
		{
			if (*(path_dest + len) == '/')
				break;
			*(path_dest + len) = '\0';
		}
	}
	else if (strcmp(pmt->tokens[1], ".") != 0)
	{
		if (*(pmt->tokens[1]) != '/' && len != 0)
			strcat(path_dest, "/");
		strcat(path_dest, pmt->tokens[1]);
	}
	if (path_dest[0] != '\0')
		change_path(pmt, path_dest, path_old);
}
