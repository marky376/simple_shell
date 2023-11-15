#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} memb_t;

#define MEMB_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(memb_t *);
} builtin_table;


/*********** a_shloop.c **************/
int n_hsh(memb_t *, char **);
int n_find_builtin(memb_t *);
void n_find_cmd(memb_t *);
void n_fork_cmd(memb_t *);

/************** a_parser.c **************/
int n_is_cmd(memb_t *, char *);
char *n_dup_chars(char *, int, int);
char *n_find_path(memb_t *, char *, char *);

/* loophsh.c */
int n_loophsh(char **);

/*********** a_errors_0.c *********/
void n_eputs(char *);
int n_eputchar(char);
int n_putfd(char c, int fd);
int n_putsfd(char *str, int fd);

/**************** a_string.c ******************/
int n_strlen(char *);
int n_strcmp(char *, char *);
char *n_starts_with(const char *, const char *);
char *n_strcat(char *, char *);

/************* a_string1.c **********/
char *n_strcpy(char *, char *);
char *n_strdup(const char *);
void n_puts(char *);
int n_putchar(char);

/************** a_exits.c *************/
char *n_strncpy(char *, char *, int);
char *n_strncat(char *, char *, int);
char *n_strchr(char *, char);

/**************** a_token.c *****************/
char **n_strtow(char *, char *);
char **n_strtow2(char *, char);

/***************** a_realloc.c **************/
char *n_memset(char *, char, unsigned int);
void n_ffree(char **);
void *n_realloc(void *, unsigned int, unsigned int);

/******************* a_memory.c **************/
int n_bfree(void **);

/************** a_custom_atoi.c ************/
int n_interactive(memb_t *);
int n_is_delim(char, char *);
int n_isalpha(int);
int n_atoi(char *);

/************ a_errors1.c ************/
int n_erratoi(char *);
void n_print_error(memb_t *, char *);
int n_print_d(int, int);
char *n_convert_number(long int, int, int);
void n_remove_comments(char *);

/************** a_builtin.c ***************/
int n_myexit(memb_t *);
int n_mycd(memb_t *);
int n_myhelp(memb_t *);

/************ a_builtin1.c *********/
int n_myhistory(memb_t *);
int n_set_alias(memb_t *, char *);
int n_unset_alias(memb_t *, char *);
int n_print_alias(list_t *);
int n_myalias(memb_t *);

/*********** a_getline.c **********/
ssize_t n_get_input(memb_t *);
int n_getline(memb_t *, char **, size_t *);
void n_sigintHandler(int);
ssize_t n_read_buf(memb_t *, char *, size_t *);
ssize_t n_input_buf(memb_t *, char **, size_t *);

/*************** a_getinfo.c **************/
void n_clear_info(memb_t *);
void n_set_info(memb_t *, char **);
void n_free_info(memb_t *, int);

/*********** a_environ.c ***************/
char *n_getenv(memb_t *, const char *);
int n_myenv(memb_t *);
int n_mysetenv(memb_t *);
int n_myunsetenv(memb_t *);
int n_populate_env_list(memb_t *);

/************* a_getenv.c ************/
char **n_get_environ(memb_t *);
int n_unsetenv(memb_t *, char *);
int n_setenv(memb_t *, char *, char *);

/************* a_history.c ***************/
char *n_get_history_file(memb_t *member);
int n_write_history(memb_t *member);
int n_read_history(memb_t *member);
int n_build_history_list(memb_t *member, char *buffer, int line_count);
int n_renumber_history(memb_t *member);

/******************* a_lists.c ******************/
list_t *n_add_node(list_t **, const char *, int);
list_t *n_add_node_end(list_t **, const char *, int);
size_t n_print_list_str(const list_t *);
int n_delete_node_at_index(list_t **, unsigned int);
void n_free_list(list_t **);

/************ a_lists1.c ************/
size_t n_list_len(const list_t *);
char **n_list_to_strings(list_t *);
size_t n_print_list(const list_t *);
list_t *n_node_starts_with(list_t *, char *, char);
ssize_t n_get_node_index(list_t *, list_t *);

/*********** a_vars.c ******************/
int n_is_chain(memb_t *, char *, size_t *);
void n_check_chain(memb_t *, char *, size_t *, size_t, size_t);
int n_replace_alias(memb_t *);
int n_replace_vars(memb_t *);
int n_replace_string(char **, char *);

#endif
