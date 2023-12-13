#include "shell.h"
/**
* hsh - Main loop for the shell.
* @inform: The parameter and return info struct.
* @av: The argument vector from main().
* Return: 0 on success, 1 on error, or an error code.
*/
int hsh(inform_t *inform, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;
while (r != -1 && builtin_ret != -2)
{
clear_inform(inform);
if (interactive(inform))
_puts("$ ");
_eputchar(BUF_FLUSH);
r = get_input(inform);
if (r != -1)
{
set_inform(inform, av);
builtin_ret = find_builtin(inform);
if (builtin_ret == -1)
find_cmd(inform);
}
else if (interactive(inform))
_putchar('\n');
free_inform(inform, 0);
}
write_history(inform);
free_inform(inform, 1);
if (!interactive(inform) && inform->status)
exit(inform->status);
if (builtin_ret == -2)
{
if (inform->err_num == -1)
exit(inform->status);
exit(inform->err_num);
}
return (builtin_ret);
}
/**
* find_builtin - Identifies a builtin command.
* @inform: The parameter and return info struct.
* Return: -1 if builtin not found,
*          0 if builtin executed successfully,
*          1 if builtin found but encountered an issue,
*         -2 if builtin signals an exit().
*/
int find_builtin(inform_t *inform)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", _ourexit},
{"env", _ourenv},
{"help", _ourhelp},
{"history", _ourhistory},
{"setenv", _oursetenv},
{"unsetenv", _ourunsetenv},
{"cd", _ourcd},
{"alias", _ouralias},
{NULL, NULL}
};
for (i = 0; builtintbl[i].type; i++)
if (_strcmp(inform->argv[0], builtintbl[i].type) == 0)
{
inform->line_count++;
built_in_ret = builtintbl[i].func(inform);
break;
}
return (built_in_ret);
}
/**
* find_cmd - Searches for a command in the PATH.
* @inform: The parameter and return info struct.
* Return: Void.
*/
void find_cmd(inform_t *inform)
{
char *path = NULL;
int i, k;
inform->path = inform->argv[0];
if (inform->linecount_flag == 1)
{
inform->line_count++;
inform->linecount_flag = 0;
}
for (i = 0, k = 0; inform->arg[i]; i++)
if (!is_delimet(inform->arg[i], " \t\n"))
k++;
if (!k)
return;
path = find_path(inform, _getenv(inform, "PATH="), inform->argv[0]);
if (path)
{
inform->path = path;
fork_cmd(inform);
}
else
{
if ((interactive(inform) || _getenv(inform, "PATH=")
|| inform->argv[0][0] == '/') && is_cmd(inform, inform->argv[0]))
fork_cmd(inform);
else if (*(inform->arg) != '\n')
{
inform->status = 127;
print_error(inform, "not found\n");
}
}
}
/**
* fork_cmd - Forks an execution thread to run a command.
* @inform: The parameter and return info struct.
* Return: Void.
*/
void fork_cmd(inform_t *inform)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(inform->path, inform->argv, get_environ(inform)) == -1)
{
free_inform(inform, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(inform->status));
if (WIFEXITED(inform->status))
{
inform->status = WEXITSTATUS(inform->status);
if (inform->status == 126)
print_error(inform, "Permission denied\n");
}
}
}
