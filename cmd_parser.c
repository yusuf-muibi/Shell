#include "shell.h"

/**
 * is_executable_command - determines if a file is an executable command
 * @shell_info: the information struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable_command(info_t *shell_info, char *file_path)
{
struct stat file_stats;

(void)shell_info;
if (!file_path || stat(file_path, &file_stats))
return (0);

if (file_stats.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
 * duplicate_characters - duplicates characters
 * @path_string: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to a new buffer
 */
char *duplicate_characters(char *path_string, int start, int stop)
{
static char buffer[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
if (path_string[i] != ':')
buffer[k++] = path_string[i];
buffer[k] = 0;
return (buffer);
}

/**
 * find_command_path - finds the command in the PATH string
 * @shell_info: the information struct
 * @path_string: the PATH string
 * @command: the command to find
 *
 * Return: full path of the command if found or NULL
 */
char *find_command_path(info_t *shell_info, char *path_string, char *command)
{
int i = 0, current_position = 0;
char *path;

if (!path_string)
return (NULL);
if ((_strlen(command) > 2) && starts_with(command, "./"))
{
if (is_executable_command(shell_info, command))
return (command);
}
while (1)
{
if (!path_string[i] || path_string[i] == ':')
{
path = duplicate_characters(path_string, current_position, i);
if (!*path)
string_concat(path, command);
else
{
string_concat(path, "/");
string_concat(path, command);
}
if (is_executable_command(shell_info, path))
return (path);
if (!path_string[i])
break;
current_position = i;
}
i++;
}
return (NULL);
}
