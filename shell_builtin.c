#include "shell.h"

/**
* custom_exit - exits the shell
* @shell_info: Structure containing potential arguments.
* Return: exits with a given exit status
*/
int custom_exit(info_t *shell_info)
{
int exit_check;

if (shell_info->argv[1])  /* If there is an exit argument */
{
exit_check = _custom_atoi(shell_info->argv[1]);
if (exit_check == -1)
{
shell_info->status = 2;
print_error_message(shell_info, "Illegal number: ");
print_error_string(shell_info->argv[1]);
print_error_char('\n');
return (1);
}
shell_info->err_num = _custom_atoi(shell_info->argv[1]);
return (-2);
}
shell_info->err_num = -1;
return (-2);
}

/**
* custom_cd - changes the current directory of the process
* @shell_info: Structure containing potential arguments.
* Return: Always 0
*/
int custom_cd(info_t *shell_info)
{
char *current_dir, *dir, buffer[1024];
int chdir_ret;

current_dir = getcwd(buffer, 1024);
if (!current_dir)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!shell_info->argv[1])
{
dir = _get_environment(shell_info, "HOME=");
if (!dir)
chdir_ret = /* TODO: what should this be? */
chdir((dir = _get_environment(shell_info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (str_compare(shell_info->argv[1], "-") == 0)
{
if (!_get_environment(shell_info, "OLDPWD="))
{
_puts(current_dir);
_putchar('\n');
return (1);
}
_puts(_get_environment(shell_info, "OLDPWD=")), _putchar('\n');
chdir_ret = /* TODO: what should this be? */
chdir((dir = _get_environment(shell_info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(shell_info->argv[1]);
if (chdir_ret == -1)
{
print_error_message(shell_info, "can't cd to ");
print_error_string(shell_info->argv[1]), print_error_char('\n');
}
else
{
set_environment_variable(shell_info, "OLDPWD", _get_environment(shell_info, "PWD="));
set_environment_variable(shell_info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
* custom_help - displays help information
* @shell_info: Structure containing potential arguments.
* Return: Always 0
*/
int custom_help(info_t *shell_info)
{
char **arg_array;

arg_array = shell_info->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array); /* temp att_unused workaround */
return (0);
}

