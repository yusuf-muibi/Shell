#include "shell.h"

/**
* check_interactive - returns true if shell is in interactive mode
* @shell_info: struct address
*
* Return: 1 if check_interactive mode, 0 otherwise
*/
int check_interactive(info_t *shell_info)
{
return (isatty(STDIN_FILENO) && shell_info->readfd <= 2);
}

/**
* is_delimiter - checks if character is a delimiter
* @c: the char to check
* @delimiter: the delimiter string
* Return: 1 if true, 0 if false
*/
int is_delimiter(char c, char *delimiter)
{
while (*delimiter)
if (*delimiter++ == c)
return (1);
return (0);
}

/**
* _isalpha - checks for alphabetic character
* @c: The character to input
* Return: 1 if c is alphabetic, 0 otherwise
*/
int _isalpha(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}

/**
* _atoi - converts a string to an integer
* @s: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*/
int _atoi(char *s)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;

for (i = 0; s[i] != '\0' && flag != 2; i++)
{
if (s[i] == '-')
sign *= -1;

if (s[i] >= '0' && s[i] <= '9')
{
flag = 1;
result *= 10;
result += (s[i] - '0');
}
else if (flag == 1)
flag = 2;
}

if (sign == -1)
output = -result;
else
output = result;

return (output);
}

