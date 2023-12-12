#include "shell.h"

/**
 * shell_loop - main shell loop
 * @shell_info: the parameter & return info struct
 * @arguments: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(info_t *shell_info, char **arguments)
{
ssize_t read_status = 0;
int builtin_return = 0;

while (read_status != -1 && builtin_return != -2)
{
initialize_info(shell_info);
if (check_interactive(shell_info))
_puts("$ ");
print_error_char(BUF_FLUSH);
read_status = get_user_input(shell_info);
if (read_status != -1)
{
populate_info(shell_info, arguments);
builtin_return = find_builtin(shell_info);
if (builtin_return == -1)
find_command(shell_info);
}
else if (check_interactive(shell_info))
_putchar('\n');
release_info(shell_info, 0);
}
save_history(shell_info);
release_info(shell_info, 1);
if (!check_interactive(shell_info) && shell_info->status)
exit(shell_info->status);
if (builtin_return == -2)
{
if (shell_info->error_number == -1)
exit(shell_info->status);
exit(shell_info->error_number);
}
return (builtin_return);
}

/**
 * find_builtin - finds a builtin command
 * @shell_info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *          0 if builtin executed successfully,
 *          1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin(info_t *shell_info)
{
int i, built_in_return = -1;
builtin_table builtintbl[] = {
{"exit",custom_exit},
{"env", custom_environment},
{"help", custom_help},
{"history", custom_history},
{"setenv", set_environment},
{"unsetenv", remove_environment},
{"cd", custom_cd},
{"alias", custom_alias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
if (str_compare(shell_info->argv[0], builtintbl[i].type) == 0)
{
shell_info->line_count++;
built_in_return = builtintbl[i].func(shell_info);
break;
}
return (built_in_return);
}

/**
 * find_command - finds a command in PATH
 * @shell_info: the parameter & return info struct
 *
 * Return: void
 */
void find_command(info_t *shell_info)
{
char *path = NULL;
int i, count_tokens;

shell_info->path = shell_info>argv[0];
if (shell_info->linecount_flag == 1)
{
shell_info->line_count++;
shell_info->linecount_flag = 0;
}
for (i = 0, count_tokens = 0; shell_info->arg[i]; i++)
if (!is_delimiter(shell_info->arg[i], " \t\n"))
count_tokens++;
if (!count_tokens)
return;

path = find_command_path(shell_info, _get_environment(shell_info, "PATH="), shell_info->argv[0]);
if (path)
{
shell_info->path = path;
fork_command(shell_info);
}
else
{
if ((check_interactive(shell_info) || _get_environment(shell_info, "PATH=")
|| shell_info->argv[0][0] == '/') && is_executable_command(shell_info, shell_info->argv[0]))
fork_command(shell_info);
else if (*(shell_info->arg) != '\n')
{
shell_info->status = 127;
print_error_message(shell_info, "not found\n");
}
}
}

/**
 * fork_command - forks an exec thread to run command
 * @shell_info: the parameter & return info struct
 *
 * Return: void
 */
void fork_command(info_t *shell_info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(shell_info->path, shell_info->argv, get_environment(shell_info)) == -1)
{
release_info(shell_info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(shell_info->status));
if (WIFEXITED(shell_info->status))
{
shell_info->status = WEXITSTATUS(shell_info->status);
if (shell_info->status == 126)
print_error_message(shell_info, "Permission denied\n");
}
}
}
