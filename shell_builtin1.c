#include "shell.h"

/**
* custom_history - displays the history list, one command by line
* @shell_info: Structure containing potential arguments.
*  Return: Always 0
*/
int custom_history(info_t *shell_info)
{
print_list_data(shell_info->command_history);
return (0);
}

/**
* remove_alias - removes alias by string
* @shell_info: parameter struct
* @str: the string alias
* Return: Always 0 on success, 1 on error
*/
int remove_alias(info_t *shell_info, char *str)
{
char *t, c;
int result;

t = custom_strchr(str, '=');
if (!t)
return (1);

c = *t;
*t = 0;
result = delete_node_at_list_index(&(shell_info->alias),
get_node_position(shell_info->alias, find_matching_node(shell_info->alias, str, -1)));
*t = c;

return (result);
}

/**
* define_alias - defines alias to string
* @shell_info: parameter struct
* @str: the string alias
* Return: Always 0 on success, 1 on error
*/
int define_alias(info_t *shell_info, char *str)
{
char *t;

t = custom_strchr(str, '=');
if (!t)
return (1);

if (!*++t)
return (remove_alias(shell_info, str));

remove_alias(shell_info, str);
return (add_list_node_end(&(shell_info->alias), str, 0) == NULL);
}

/**
* print_alias_string - prints an alias string
* @node: the alias node
* Return: Always 0 on success, 1 on error
*/
int print_alias_string(list_t *node)
{
char *t = NULL, *alias = NULL;

if (node)
{
t = custom_strchr(node->str, '=');
for (alias = node->str; alias <= t; alias++)
_putchar(*alias);
_putchar('\'');
_puts(t + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
* custom_alias - mimics the alias builtin
* @shell_info: Structure containing potential arguments.
* Return: Always 0
*/
int custom_alias(info_t *shell_info)
{
int i = 0;
char *t = NULL;
list_t *node = NULL;

if (shell_info->argc == 1)
{
node = shell_info->alias;
while (node)
{
print_alias_string(node);
node = node->next;
}
return (0);
}

for (i = 1; shell_info->argv[i]; i++)
{
t = custom_strchr(shell_info->argv[i], '=');
if (t)
define_alias(shell_info, shell_info->argv[i]);
else
print_alias_string(find_matching_node(shell_info->alias, shell_info->argv[i], '='));
}

return (0);
}
