#ifndef SHELL_HEADER
#define SHELL_HEADER

/*== libraries ==*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdarg.h>

#ifdef _WIN32
#include <windows.h>
#endif
/*===== end =====*/

/*=== macros ===*/
#define MAX_BUFFSIZE 1024
/*==== end ====*/

/*== structs ==*/
/**
 * struct Parameters - struct content parameters for my functions
 * @environment: content of current environment variables
 * @name_shell: name of my shell
 * @command: command insert by user
 * @tokens: command split
 * @band: verify changes in the environment variables
 * @lines: counter lines
 * @input_type: 0 mood no interactive, 1 mood interactive
 * @count_exit: count exit entry
 *
 * Description: longer description
 */
typedef struct Parameters
{
	char **environment;
	char *name_shell;
	char *command;
	char **tokens;
	int  band;
	int lines;
	int input_type;
	int count_exit;
} st_parameters;
/**
 * struct cmd_clean - struct content name a function custom of my shell
 * @name: name function custom
 * @f: pointer function custom
 *
 * Description: longer Description
 */
typedef struct cmd_clean
{
	char *name;
	void (*f)(st_parameters *);
} cmd_t;
/*===== end =====*/

/*== functions ==*/

/* functions_main.c */
void validate_commands(st_parameters *);
void command_systems(st_parameters *);
void command_customs(st_parameters *);
void (*matcher(char *))(st_parameters *);

/* functions_custom.c */
void shell_env(st_parameters *);
void shell_clear(st_parameters *);
void shell_exit(st_parameters *);
void shell_ctrl(st_parameters *);
void shell_signal(int);
void shell_setenv(st_parameters *);
void shell_unsetenv(st_parameters *pmt);
void shell_cd(st_parameters *pmt);
void shell_printenv(st_parameters *pmt);

/* functions_libraries.c */
ssize_t my_gline(char **lineptr, size_t *n, FILE *stream);
char *my_strtok(char *buffer, const char *delimiter);
char *my_getenv(char *key, char **env, int mood);
int my_access(int *band, char **, st_parameters *pmt);

/* functions_helps.c */
void _setenv(char **new_variable, char *key, char *value, st_parameters *pmt);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _atoi(char *);
char *_strdup(char *buffer);
void _trim(char **str);
void _free(char **ptr);
char **_drealloc(char **src, size_t size, size_t add, char **list, int mood);
unsigned int _dstrlen(char **ptr);
void _concat(char **buff, int n, ...);
char *to_str(int n);
void init_struct(st_parameters *pmt, char **argv, char **env);
/*===== end =====*/

#endif
