#include "shell.h"
/**
* is_cmd - Checks if a file is an executable command.
* @inform: The information struct.
* @path: The path to the file.
* Return: 1 if true, 0 otherwise.
*/
int is_cmd(inform_t *inform, char *path)
{
struct stat st;

(void)inform;
if (!path || stat(path, &st))
return (0);

if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}
/**
* dup_chars - Creates a duplicate of characters within a specified range.
* @pathstr: The PATH string.
* @start: Starting index.
* @stop: Stopping index.
* Return: Pointer to the new buffer.
*/
char *dup_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;
for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}
/**
* find_path - Locates the specified command in the PATH string.
* @inform: The information struct.
* @pathstr: The PATH string.
* @cmd: The command to find.
* Return: Full path of the command if found, or NULL.
*/
char *find_path(inform_t *inform, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;
if (!pathstr)
return (NULL);
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_cmd(inform, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = dup_chars(pathstr, curr_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (is_cmd(inform, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
