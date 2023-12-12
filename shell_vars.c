#include "shell.h"

/**
* is_command_chain - tests if the current char in buffer is a chain delimiter
* @shell_info: the parameter struct
* @buffer: the char buffer
* @position: address of the current position in buffer
* Return: 1 if chain delimiter, 0 otherwise
*/
int is_command_chain(info_t *shell_info, char *buffer, size_t *position)
{
size_t j = *position;

if (buffer[j] == '|' && buffer[j + 1] == '|')
{
buffer[j] = 0;
j++;
shell_info->cmd_buf_type = CMD_OR;
}
else if (buffer[j] == '&' && buffer[j + 1] == '&')
{
buffer[j] = 0;
j++;
shell_info->cmd_buf_type = CMD_AND;
}
else if (buffer[j] == ';') /* found end of this command */
{
buffer[j] = 0; /* replace semicolon with null */
shell_info->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*position = j;
return (1);
}

/**
* check_cmd_chain - checks if to continue chaining based on the last status
* @shell_info: the parameter struct
* @buffer: the char buffer
* @position: address of the current position in buffer
* @start: starting position in buffer
* @length: length of buffer
* Return: Void
*/
void check_cmd_chain(info_t *shell_info,
char *buffer, size_t *position, size_t start, size_t length)
{
size_t j = *position;

if (shell_info->cmd_buf_type == CMD_AND)
{
if (shell_info->status)
{
buffer[start] = 0;
j = length;
}
}
if (shell_info->cmd_buf_type == CMD_OR)
{
if (!shell_info->status)
{
buffer[start] = 0;
j = length;
}
}

*position = j;
}

/**
* replace_cmd_alias - replaces an alias in the tokenized string
* @shell_info: the parameter struct
* Return: 1 if replaced, 0 otherwise
*/
int replace_cmd_alias(info_t *shell_info)
{
int i;
list_t *node;
char *p;

for (i = 0; i < 10; i++)
{
node = find_matching_node(shell_info->alias, shell_info->argv[0], '=');
if (!node)
return (0);
free(shell_info->argv[0]);
p = custom_strchr(node->str, '=');
if (!p)
return (0);
p = string_duplicate(p + 1);
if (!p)
return (0);
shell_info->argv[0] = p;
}
return (1);
}

/**
* replace_cmd_vars - replaces vars in the tokenized string
* @shell_info: the parameter struct
* Return: 1 if replaced, 0 otherwise
*/
int replace_cmd_vars(info_t *shell_info)
{
int i = 0;
list_t *node;

for (i = 0; shell_info->argv[i]; i++)
{
if (shell_info->argv[i][0] != '$' || !shell_info->argv[i][1])
continue;

if (!str_compare(shell_info->argv[i], "$?"))
{
replace_string_content(&(shell_info->argv[i]),
string_duplicate(convert_to_string(shell_info->status, 10, 0)));
continue;
}
if (!str_compare(shell_info->argv[i], "$$"))
{
replace_string_content(&(shell_info->argv[i]),
string_duplicate(convert_to_string(getpid(), 10, 0)));
continue;
}
node = find_matching_node(shell_info->env, &shell_info->argv[i][1], '=');
if (node)
{
replace_string_content(&(shell_info->argv[i]),
string_duplicate(custom_strchr(node->str, '=') + 1));
continue;
}
replace_string_content(&shell_info->argv[i], string_duplicate(""));

}
return (0);
}

/**
* replace_string_content - replaces string content
* @old_content: address of the old string content
* @new_content: new string content
* Return: 1 if replaced, 0 otherwise
*/
int replace_string_content(char **old_content, char *new_content)
{
free(*old_content);
*old_content = new_content;
return (1);
}
