#include "shell.h"
#define BEFOREPROMPT (OUT CLSCBLUE_BG)
#define MIDWEL (CLCREMA_BG)
#define AFTERPATH ("    |" RESET OUT"\n> ")
/**
 * print_prompt - show prompt for the user
 * @pmt: pointer to structure with members related to user input
 **/
void print_prompt(st_parameters *pmt)
{
	char *path = my_getenv("PWD", pmt->environment, 0);

	if (pmt->lines < 1)
	{
		printf(CLSCBLUE"******************************************\n");
		printf("*\n");
		printf("*\n");
		printf("*    Project:\n");
		printf("*		"RESET"SIMPLE SHELL\n"CLSCBLUE);
		printf("*    Authors:\n");
		printf("*		"RESET"- Miguel Barrera\n"CLSCBLUE);
		printf("*		"RESET"- Cristhian Apaza\n"CLSCBLUE);
		printf("*\n");
		printf("*\n");
		printf("******************************************\n\n");
	}
	(void)pmt;
	write(STDOUT_FILENO, BEFOREPROMPT, strlen(BEFOREPROMPT));

	write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
	write(STDOUT_FILENO, MIDWEL, strlen(MIDWEL));
	write(STDOUT_FILENO, path, strlen(path));
	write(STDOUT_FILENO, AFTERPATH, strlen(AFTERPATH));
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
	pmt->status = 0;
	pmt->code = 0;
	pmt->tokens = NULL;
}
/**
 * read_input - function that read data of the user
 * @pmt: pointer to structure with members related to user input
 */
void read_input(st_parameters *pmt)
{
	size_t len = 0;

	/* info - Check the file descriptor reference */
	pmt->lines += 1;
	pmt->size_cmd = getline(&(pmt->command), &len, stdin);
	/* info - Exit my shell options "crtl + D" */
	if (pmt->size_cmd == EOF)
		pmt->status = -1;
	else
	{
		/* info - Remove blanks at start */
		_trim(&(pmt->command));
		pmt->size_cmd = strlen(pmt->command);
	}
}
/**
 * parse_input - function that modify the data of the user
 * @pmt: pointer to structure with members related to user input
 */
void parse_input(st_parameters *pmt)
{
	size_t i = 0;

	pmt->tokens = malloc(sizeof(char *) * 50);

	for (i = 0; (pmt->tokens[i] = my_strtok(pmt->command, " \t\n")) != NULL; i++)
		pmt->command = NULL;
	free(pmt->command);
}
