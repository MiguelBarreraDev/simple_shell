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
#include <linux/limits.h>
#include <limits.h>

#ifdef _WIN32
#include <windows.h>
#endif
/*===== end =====*/

/*==== macros ====*/
#define PROMPT "|  #Cisfun$    "
#define MAX_BUFFSIZE 1024
/* Colors */
#define RESET "\x1b[0m"
#define NEGRprint_O_T "\x1b[30m"
#define NEGRO_F "\x1b[40m"
#define ROJO_T "\x1b[31m"
#define ROJO_F "\x1b[41m"
#define VERDE_T "\x1b[32m"
#define VERDE_F "\x1b[42m"
#define AMARILLO_T "\x1b[33m"
#define AMARILLO_F "\x1b[43m"
#define AZUL_T "\x1b[34m"
#define AZUL_F "\x1b[44m"
#define MAGENTA_T "\x1b[35m"
#define MAGENTA_F "\x1b[45m"
#define CYAN_T "\x1b[36m"
#define CYAN_F "\x1b[46m"
#define BLANCO_T "\x1b[37m"
#define BLANCO_F "\x1b[47m"
#define CLSCBLUE "\x1b[0;1;38;5;81;48;0;240m"
#define CLSCBLUE_BG "\x1b[0;1;38;5;81;48;5;240m"
#define CLCREMA "\x1b[0;1;38;5;221;48;0;240m"
#define CLCREMA_BG "\x1b[0;1;38;5;221;48;5;240m"
#define OUT "\x1b[0;1m"
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
 * @size_cmd: length of the command
 * @status: program status
 * @code: exit code
 *
 * Description: longer description
 */
typedef struct Parameters
{
	char **environment;
	char *name_shell;
	char *command;
	char **tokens;
	ssize_t size_cmd;
	int band;
	int lines;
	int input_type;
	ssize_t status;
	int code;
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
int validate_number(char *str_number);
/* functions_IO */
void init_struct(st_parameters *pmt, char **argv, char **env);
void read_input(st_parameters *pmt);
void parse_input(st_parameters *pmt);
void print_prompt(st_parameters *pmt);

/* functions_parts */
void change_path(st_parameters *pmt, char pwd[PATH_MAX], char old[PATH_MAX]);
void shell_cd_arg(st_parameters *pmt, char path_dest[], char path_old[]);

/* functions_handler */
void handler_status(st_parameters *pmt);
void generator_message(st_parameters *pmt, char *message);
/*===== end =====*/

#endif
