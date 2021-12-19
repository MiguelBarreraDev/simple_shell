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

	init_struct(&pmt, argv, env);
	signal(SIGINT, shell_signal);

	pmt.input_type = isatty(STDIN_FILENO);

	while (1)
	{
		if (pmt.input_type == 1)
			print_prompt(&pmt);

		read_input(&pmt);
		if (pmt.size_cmd > 1)
		{
			parse_input(&pmt);
			validate_commands(&pmt);
		}
		handler_status(&pmt);
		if (pmt.status == -1)
		{
			free(pmt.command);
			if (pmt.band == 1)
				_free(pmt.environment);
			exit(pmt.code);
		}
		free(pmt.command);
		write(STDIN_FILENO, "\n", 1);
	}
	return (0);
}
