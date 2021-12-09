#include "shell.h"
/**
 * main - function where the shell starts
 * @argc: number of arguments passed to the program
 * @argv: Variable that points to a list in memory
 * where the arguments are located
 * @env: Points to the memory space where the system
 * environment variables are located
 *
 * Return: 0 it if succeeds, antoher it if fails
 */
int main(int argc __attribute__((unused)), char **argv, char **env)
{
	st_parameters pmt;
	size_t sz_buffer;
	char *prompt = ":) ";
	int r_getline = 0, i = 0;

	init_struct(&pmt, argv, env);
	signal(SIGINT, shell_signal);
	pmt.input_type = isatty(STDIN_FILENO);
	pmt.count_exit = 0;
	while (1)
	{
		sz_buffer = 0, r_getline = 0;
		/* info - Check the file descriptor reference */
		if (pmt.input_type == 1)
		{
			write(STDOUT_FILENO, prompt, strlen(prompt));
		}
		pmt.lines += 1;
		r_getline = getline(&(pmt.command), &sz_buffer, stdin);
		/* info - Exit my shell options "crtl + D" */
		if (r_getline == EOF)
			break;
		/* info - Remove blanks at start */
		_trim(&(pmt.command));
		/* info - Controlling line break "\n" */
		if (strlen(pmt.command) <= 1)
		{
			free(pmt.command);
			continue;
		}
		for (i = 0; (pmt.tokens[i] = my_strtok(pmt.command, " \t\n")) != NULL; i++)
			pmt.command = NULL;
		validate_commands(&pmt);
		free(pmt.tokens[0]), free(pmt.command);
	}
	free(pmt.tokens), free(pmt.command);
	if (pmt.band == 1)
		_free(pmt.environment);
	return (0);
}
/**
 * init_struct - function that initializing Parameters structure
 * @pmt: pointer to Parameters structure
 * @argv: pointer to list of arguments of the main functions
 * @env: pointer to memory space of the environment variables
 */
void init_struct(st_parameters *pmt, char **argv, char **env)
{
	pmt->command = NULL;
	pmt->name_shell = argv[0];
	pmt->environment = env;
	pmt->band = 0;
	pmt->lines = 0;
	pmt->input_type = 0;
	/* info - IMPORT! reserved memory */
	pmt->tokens = malloc(sizeof(char *) * 50);
}
