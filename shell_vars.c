#include "shell.h"
/**
* is_chain - Checks if the current character in the buffer is a chain delimiter.
* @inform: The parameter struct.
* @buf: The character buffer.
* @p: The address of the current position in the buffer.
* Return: 1 if it's a chain delimiter, 0 otherwise.
*/
int is_chain(inform_t *inform, char *buf, size_t *p)
{
size_t j = *p;
if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
inform->cmd_buf_type = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
inform->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ';') /* found end of this command */
{
buf[j] = 0; /* replace semicolon with null */
inform->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = j;
return (1);
}
/**
* check_chain - Examines whether we should continue chaining based on the last status.
* @inform: The parameter struct.
* @buf: The character buffer.
* @p: The address of the current position in the buffer.
* @i: The starting position in the buffer.
* @len: The length of the buffer.
* Return: Void.
*/
void check_chain(inform_t *inform, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;
if (inform->cmd_buf_type == CMD_AND)
{
if (inform->status)
{
buf[i] = 0;
j = len;
}
}
if (inform->cmd_buf_type == CMD_OR)
{
if (!inform->status)
{
buf[i] = 0;
j = len;
}
}
*p = j;
}
/**
* replace_alias - Substitutes aliases in the tokenized string.
* @inform: The parameter struct.
* Return: 1 if replaced, 0 otherwise.
*/
int replace_alias(inform_t *inform)
{
int i;
list_t *node;
char *p;
for (i = 0; i < 10; i++)
{
node = node_starts_with(inform->alias, inform->argv[0], '=');
if (!node)
return (0);
free(inform->argv[0]);
p = _strchr(node->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
inform->argv[0] = p;
}
return (1);
}
/**
* replace_vars - Substitutes variables in the tokenized string.
* @inform: The parameter struct.
* Return: 1 if replaced, 0 otherwise.
*/
int replace_vars(inform_t *inform)
{
int i = 0;
list_t *node;
for (i = 0; inform->argv[i]; i++)
{
if (inform->argv[i][0] != '$' || !inform->argv[i][1])
continue;
if (!_strcmp(inform->argv[i], "$?"))
{
replace_string(&(inform->argv[i]),
_strdup(convert_number(inform->status, 10, 0)));
continue;
}
if (!_strcmp(inform->argv[i], "$$"))
{
replace_string(&(inform->argv[i]),
_strdup(convert_number(getpid(), 10, 0)));
continue;
}
node = node_starts_with(inform->env, &inform->argv[i][1], '=');
if (node)
{
replace_string(&(inform->argv[i]),
_strdup(_strchr(node->str, '=') + 1));
continue;
}
replace_string(&inform->argv[i], _strdup(""));
}
return (0);
}
/**
* replace_string - Substitutes a string.
* @old: The address of the old string.
* @new: The new string.
* Return: 1 if replaced, 0 otherwise.
*/
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
