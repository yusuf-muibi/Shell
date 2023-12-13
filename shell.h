#ifndef _SHELL_H_
#define _SHELL_H_

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
#define CMD_NORM		0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN		3

/* for convert_number() */
#define CONVERT_LOWERCASE		1
#define CONVERT_UNSIGNED		2

/* 1 if using system getline() */
#define USE_GETLINE	0
#define USE_STRTOK		0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
* struct liststr - Singly linked list structure.
* @num: Numeric field.
* @str: String field.
* @next: Pointer to the next node.
*/
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
* struct passinform - Container for pseudo-arguments to pass into a function,
*                     enabling a uniform prototype for a function pointer struct.
*
* @arg: A string generated from getline containing arguments.
* @argv: An array of strings generated from arg.
* @path: A string path for the current command.
* @argc: The argument count.
* @line_count: The error count.
* @err_num: The error code for exit()s.
* @linecount_flag: If on, count this line of input.
* @fname: The program filename.
* @env: Linked list local copy of environ.
* @environ: Custom modified copy of environ from LL env.
* @history: The history node.
* @alias: The alias node.
* @env_changed: On if environ was changed.
* @status: The return status of the last exec'd command.
* @cmd_buf: Address of pointer to cmd_buf, on if chaining.
* @cmd_buf_type: CMD_type ||, &&, ;
* @readfd: The fd from which to read line input.
* @histcount: The history line number count.
*/
typedef struct passinform
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
} inform_t;

#define INFORM_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
        0, 0, 0}

/**
* struct builtin - Container for a builtin string and its related function.
* @type: The builtin command flag.
* @func: The associated function.
*/
typedef struct builtin
{
        char *type;
        int (*func)(inform_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(inform_t *, char **);
int find_builtin(inform_t *);
void find_cmd(inform_t *);
void fork_cmd(inform_t *);

/* toem_parser.c */
int is_cmd(inform_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(inform_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoies.c */
int interactive(inform_t *);
int is_delimet(char, char *);
int _isalpha(int);
int _atoies(char *);

/* toem_errors1.c */
int _erratoies(char *);
void print_error(inform_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _ourexit(inform_t *);
int _ourcd(inform_t *);
int _ourhelp(inform_t *);

/* toem_builtin1.c */
int _ourhistory(inform_t *);
int _ouralias(inform_t *);

/*toem_getline.c */
ssize_t get_input(inform_t *);
int _getline(inform_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_inform(inform_t *);
void set_inform(inform_t *, char **);
void free_inform(inform_t *, int);

/* toem_environ.c */
char *_getenv(inform_t *, const char *);
int _ourenv(inform_t *);
int _oursetenv(inform_t *);
int _ourunsetenv(inform_t *);
int populate_env_list(inform_t *);

/* toem_getenv.c */
char **get_environ(inform_t *);
int _unsetenv(inform_t *, char *);
int _setenv(inform_t *, char *, char *);

/* toem_history.c */
char *get_history_file(inform_t *inform);
int write_history(inform_t *inform);
int read_history(inform_t *inform);
int build_history_list(inform_t *inform, char *buf, int linecount);
int renumber_history(inform_t *inform);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(inform_t *, char *, size_t *);
void check_chain(inform_t *, char *, size_t *, size_t, size_t);
int replace_alias(inform_t *);
int replace_vars(inform_t *);
int replace_string(char **, char *);

#endif
