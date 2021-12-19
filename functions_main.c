#include  "shell.h"
#include <errno.h>
/**
 * validate_commands - validates the existence and execution
 * permissions of the command entered by the user
 * @pmt: pointer to structure with members related to user input
 */
void validate_commands(st_parameters *pmt)
{
	ssize_t validate_cmd;
	char *buffer;
	int band = 0;
	char *tmp_free = NULL;

	tmp_free = pmt->tokens[0];

	validate_cmd = my_access(&band, &buffer, pmt);

	if (validate_cmd == -1)
		command_customs(pmt);
	else
		command_systems(pmt);

	/* @band: variable to recognize the format of the first token */
	if (band == 1)
	{
		pmt->tokens[0] = tmp_free;
		free(buffer);
	}
}
/**
 * command_systems - executes the command entered, which belongs to the system
 * @pmt: pointer to structure with members related to user input
 */
void command_systems(st_parameters *pmt)
{
	pid_t id_proccess = 0;
	int code = 0;

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
			wait(&code);
			if (code == 512)
				code = 2;
			pmt->code = code;
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

	f = matcher(pmt->tokens[0]);
	if (f == NULL)
		pmt->status = 127;
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
