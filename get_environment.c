#include "shell.h"

/**
* _get_environment - returns the string array copy of our environment
* @shell_info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* Return: Always 0
*/
char **get_environment(info_t *shell_info)
{
if (!shell_info->environ || shell_info->env_changed)
{
shell_info->environ = list_to_str_array(shell_info->env);
shell_info->env_changed = 0;
}

return (shell_info->environ);
}

/**
* remove_environment_variable - Remove an environment variable
* @shell_info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* @variable: the string env var property
* Return: 1 on delete, 0 otherwise
*/
int remove_environment_variable(info_t *shell_info, char *variable)
{
list_t *node = shell_info->env;
size_t i = 0;
char *p;

if (!node || !variable)
return (0);

while (node)
{
p = starts_with(node->str, variable);
if (p && *p == '=')
{
shell_info->env_changed = delete_node_at_list_index(&(shell_info->env), i);
i = 0;
node = shell_info->env;
continue;
}
node = node->next;
i++;
}
return (shell_info->env_changed);
}

/**
* set_environment_variable - Initialize a new environment variable,
*             or modify an existing one
* @shell_info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* @variable: the string env var property
* @value: the string env var value
* Return: Always 0
*/
int set_environment_variable(info_t *shell_info, char *variable, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!variable || !value)
return (0);

buf = malloc(_strlen(variable) + _strlen(value) + 2);
if (!buf)
return (1);
string_copy(buf, variable);
string_concat(buf, "=");
string_concat(buf, value);
node = shell_info->env;
while (node)
{
p = starts_with(node->str, variable);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
shell_info->env_changed = 1;
return (0);
}
node = node->next;
}
add_list_node_end(&(shell_info->env), buf, 0);
free(buf);
shell_info->env_changed = 1;
return (0);
}
