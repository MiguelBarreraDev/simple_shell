#include  "shell.h"
#define MAX 1024
/**
 * validate_commands - validates the existence and execution
 * permissions of the command entered by the user
 * @pmt: pointer to structure with members related to user input
 */
void validate_commands(st_parameters *pmt)
{
	char **tokens = pmt->tokens;
	ssize_t validador;
	char buffer1[MAX];
	const char *str1 = "/bin/", *str2 = NULL;
	int band = 0;
	char *tmp_free = NULL;

	tmp_free = pmt->tokens[0];

	if (tokens[0] && tokens[0][0] != '/')
	{
		str2 = tokens[0];
		band = 1;
		memccpy((char *)memccpy(buffer1, str1, '\0', MAX) - 1, str2, '\0', MAX);
		tokens[0] = buffer1;
	}

	validador = access(tokens[0], X_OK);
	if (validador == -1)
	{
		/* @band: variable to recognize the format of the first token */
		if (band == 1)
			pmt->tokens[0] = tmp_free;
		command_customs(pmt);
	}
	else
	{
		command_systems(pmt);
		/* @band: variable to recognize the format of the first token */
		if (band == 1)
			pmt->tokens[0] = tmp_free;
	}
}
/**
 * command_systems - executes the command entered, which belongs to the system
 * @pmt: pointer to structure with members related to user input
 */
void command_systems(st_parameters *pmt)
{
	pid_t id_proccess = 0;

	id_proccess = fork();
	switch (id_proccess)
	{
		case -1:
			break;
		case 0:
			execve(pmt->tokens[0], pmt->tokens, pmt->environment);
			kill(getpid(), SIGKILL);
			break;
		default:
			wait(NULL);
			break;
	}

}
/**
 * command_customs - run the entered command that belongs to custom commands
 * @pmt: pointer to structure with members related to user input
 */
void command_customs(st_parameters *pmt)
{
	void (*f)(st_parameters *);
	char *shell = pmt->name_shell;
	char *input = pmt->tokens[0];
	char *str_err = NULL;
	char *lines;
	char *s = ": ";
	char *err = ": not found\n";

	/* info - select function custom */
	f = matcher(pmt->tokens[0]);
	if (f == NULL)
	{
		if (pmt->input_type == 1)
		{
			perror(shell);
		}
		else
		{
			lines = to_str(pmt->lines);
			_concat(&str_err, 6, shell, s, lines, s, input, err);
			free(str_err);
			free(lines);
		}
	}
	else
		f(pmt);
}

/**
 * matcher - Check the agreement between the command
 * entered and the list of program commands
 * @entry_cmd: command entered by the user
 *
 * Return: a pointer to the function that matches the command entered
 */
void (*matcher(char *entry_cmd))(st_parameters *)
{
	int i = 0;

	cmd_t cmd[] = {
		{"clear", shell_clear},
		{"env", shell_env},
		{"printenv", shell_env},
		{"exit", shell_exit},
		{"setenv", shell_setenv},
		{"unsetenv", shell_unsetenv},
		{"cd", shell_cd},
		{"printenv", shell_printenv},
		{NULL, NULL}
	};
	while (cmd[i].name != NULL)
	{
		if (strcmp(entry_cmd, cmd[i].name) == 0)
			return (cmd[i].f);
		i++;
	}
	return (cmd[i].f);
}
