#include "shell.h"

/**
 * get_history_filepath - Retrieves the history file path
 * @shell_info: Parameter struct
 * Return: Allocated string containing the history file path
 */
char *get_history_filepath(info_t *shell_info)
{
char *buffer, *home_dir,

dir = get_environment(shell_info, "HOME=");
if (!dir)
return (NULL);

file_path = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HISTORY_FILE) + 2));
if (!buf)
return (NULL);

buf[0] = 0;
string_copy(buf, dir);
string_concat(buf, "/");
string_concat(buf, HISTORY_FILE);

return (buf);
}

/**
 * save_history - Creates or appends to the history file
 * @shell_info: The parameter struct
 *
 * Return: 1 on success, else -1
 */
int save_history(info_t *shell_info)
{
ssize_t file_desc;
char *file_name = get_history_filepath(shell_info);
list_t *node = NULL;

if (!file_name)
return (-1);

file_desc = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(file_name);

if (file_desc == -1)
return (-1);

for (node = shell_info->command_history; node; node = node->next)
{
print_string_to_fd(node->str, file_desc);
print_to_fd('\n', file_desc);
}

print_to_fd(BUF_FLUSH, file_desc);
close(file_desc);

return (1);
}

/**
 * load_history - Reads history from the file
 * @shell_info: The parameter struct
 *
 * Return: HistCount on success, 0 otherwise
 */
int load_history(info_t *shell_info)
{
int i, last = 0, line_count = 0;
ssize_t file_desc, read_len, file_size = 0;
struct stat st;
char *buf = NULL, *file_name = get_history_filepath(shell_info);

if (!file_name)
return (0);

file_desc = open(file_name, O_RDONLY);
free(file_name);

if (file_desc == -1)
return (0);

if (!fstat(file_desc, &st))
file_size = st.st_size;

if (file_size < 2)
return (0);

buf = malloc(sizeof(char) * (file_size + 1));
if (!buf)
return (0);

read_len = read(file_desc, buf, file_size);
buf[file_size] = 0;

if (read_len <= 0)
return (free(buf), 0);

close(file_desc);

for (i = 0; i < file_size; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
add_history_entry(shell_info, buf + last, line_count++);
last = i + 1;
}

if (last != i)
add_history_entry(shell_info, buf + last, line_count++);

free(buf);
shell_info->history_count = line_count;

while (shell_info->history_count-- >= HISTORY_MAX)
delete_node_at_index(&(shell_info->command_history), 0);

renumber_history(shell_info);

return (shell_info->history_count);
}

/**
 * add_history_entry - Adds an entry to a history linked list
 * @shell_info: Structure containing potential arguments. Used to maintain
 * @buf: Buffer
 * @line_count: The history line_count, history_count
 *
 * Return: Always 0
 */
int add_history_entry(info_t *shell_info, char *buf, int line_count)
{
list_t *node = NULL;

if (shell_info->command_history)
node = shell_info->command_history;

add_node_end(&node, buf, line_count);

if (!shell_info->command_history)
shell_info->command_history = node;

    return (0);
}

/**
 * update_history_count - Renumbers the history linked list after changes
 * @shell_info: Structure containing potential arguments. Used to maintain
 *
 * Return: The new history_count
 */
int update_history_count(info_t *shell_info)
{
list_t *node = shell_info->command_history;
int i = 0;

while (node)
{
node->num = i++;
node = node->next;
}

return (shell_info->history_count = i);
}
