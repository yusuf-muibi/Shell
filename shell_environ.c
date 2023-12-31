#include "shell.h"

/**
* custom_environment - prints the current environment
* @shell_info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int custom_environment(info_t *shell_info)
{
print_list_data(shell_info->env);
return (0);
}

/**
* _get_environment - gets the value of an environ variable
* @shell_info: Structure containing potential arguments.
* @name: environment variable name
* Return: the value
 */
char *_get_environment(info_t *shell_info, const char *name)
{
list_t *node = shell_info->env;
char *t;

while (node)
{
t = starts_with(node->str, name);
if (t && *t)
return (t);
node = node->next;
}
return (NULL);
}

/**
* set_environment - Initialize a new environment variable or modify an old one
* @shell_info: Structure containing potential arguments.
*  Return: Always 0
*/
int set_environment(info_t *shell_info)
{
if (shell_info->argc != 3)
{
print_error_string("Incorrect number of arguements\n");
return (1);
}
if (set_environment_variable(shell_info,
shell_info->argv[1], shell_info->argv[2]))
return (0);
return (1);
}

/**
* remove_environment - Remove an environment variable
* @shell_info: Structure containing potential arguments.
*  Return: Always 0
*/
int remove_environment(info_t *shell_info)
{
int i;

if (shell_info->argc == 1)
{
print_error_string("Too few arguments.\n");
return (1);
}
for (i = 1; i <= shell_info->argc; i++)
remove_environment_variable(shell_info, shell_info->argv[i]);

return (0);
}

/**
* populate_environment_list - populates environment
* @shell_info: Structure containing potential arguments.
* Return: Always 0
*/
int populate_environment_list(info_t *shell_info)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_list_node_end(&node, environ[i], 0);
shell_info->env = node;
return (0);
}
