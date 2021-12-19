#include "shell.h"
/**
 * handler_status - controls the different states of the program
 * @pmt: pointer to structure with members related to user input
 */
void handler_status(st_parameters *pmt)
{
	ssize_t status = pmt->status;
	int code = pmt->code;
	char *err = NULL;

	switch (status)
	{
		case -1:
			pmt->code = code;
			break;
		case 127:
			pmt->code = 127;
			_concat(&err, 1, "not found\n");
			generator_message(pmt, err);
			break;
		case 2:
			pmt->code = 2;
			_concat(&err, 3, "Illegal number: ", pmt->tokens[1], "\n");
			generator_message(pmt, err);
			break;

	}
	if ((status != -1 || status == -1) && pmt->size_cmd > 1)
	{
		free(pmt->tokens[0]);
		free(pmt->tokens);
	}
}
/**
 * generator_message - generates the error messages
 * @pmt: pointer to structure with members related to user input
 * @message: custom message part
 */
void generator_message(st_parameters *pmt, char *message)
{
	char *shell = pmt->name_shell;
	char *input = pmt->tokens[0];
	char *str_err = NULL;
	char *lines;
	char *s = ": ";

	lines = to_str(pmt->lines);
	_concat(&str_err, 7, shell, s, lines,
		s, input, s, message);
	write(STDERR_FILENO, str_err, strlen(str_err));
	free(message);
	free(str_err);
	free(lines);
}
