#include "shell.h"

/**
* initialize_info - Clears and initializes the info_t struct
* @shell_info: The struct address to be initialized
*/
void initialize_info(info_t *shell_info)
{
shell_info->arg = NULL;
shell_info->argv = NULL;
shell_info->path = NULL;
shell_info->argc = 0;
}

/**
* populate_info - Initializes the info_t struct with arguments
* @shell_info: The struct address to be populated
* @argument_vector: The argument vector
*/
void populate_info(info_t *shell_info, char **argument_vector)
{
int i = 0;

shell_info->fname = argument_vector[0];
if (shell_info->arg)
{
shell_info->argv = split_string(shell_info->arg, " \t");
if (!shell_info->argv)
{
shell_info->argv = malloc(sizeof(char *) * 2);
if (shell_info->argv)
{
shell_info->argv[0] = string_duplicate(shell_info->arg);
shell_info->argv[1] = NULL;
}
}
for (i = 0; shell_info->argv && shell_info->argv[i]; i++)
;
shell_info->argc = i;

replace_cmd_alias(shell_info);
replace_cmd_vars(shell_info);
}
}

/**
* release_info - Frees memory allocated for fields in the info_t struct
* @shell_info: The struct address to be released
* @all: True if freeing all fields
*/
void release_info(info_t *shell_info, int all)
{
ffree(shell_info->argv);
shell_info->argv = NULL;
shell_info->path = NULL;
if (all)
{
if (!shell_info->cmd_buf)
free(shell_info->arg);
if (shell_info->env)
free_list_nodes(&(shell_info->env));
if (shell_info->command_history)
free_list_nodes(&(shell_info->command_history));
if (shell_info->alias)
free_list_nodes(&(shell_info->alias));
ffree(shell_info->environ);
shell_info->environ = NULL;
free_and_nullify((void **)shell_info->cmd_buf);
if (shell_info->readfd > 2)
close(shell_info->readfd);
_putchar(BUF_FLUSH);
}
}
