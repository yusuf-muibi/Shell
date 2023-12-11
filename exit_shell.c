#include "shell.h"

/**
* custom_strncpy - copies a string up to a specified number of characters
* @dest: the destination string to be copied to
* @src: the source string
* @n: the maximum number of characters to be copied
* Return: a pointer to the destination string
*/
char *custom_strncpy(char *dest, char *src, int n)
{
int i, j;
char *result = dest;

i = 0;
while (src[i] != '\0' && i < n - 1)
{
dest[i] = src[i];
i++;
}

if (i < n)
{
j = i;
while (j < n)
{
dest[j] = '\0';
j++;
}
}

return (result);
}

/**
* custom_strncat - concatenates two strings to specified number of char
* @dest: the first string
* @src: the second string
* @n: the maximum number of bytes to be used
* Return: a pointer to the concatenated string
*/
char *custom_strncat(char *dest, char *src, int n)
{
int i, j;
char *result = dest;

i = 0;
j = 0;

while (dest[i] != '\0')
i++;

while (src[j] != '\0' && j < n)
{
dest[i] = src[j];
i++;
j++;
}

if (j < n)
dest[i] = '\0';

return (result);
}

/**
* custom_strchr - locates a character in a string
* @s: the string to be parsed
* @c: the character to look for
* Return: a pointer to the first occurrence of the character in the string,
*         or NULL if the character is not found
*/
char *custom_strchr(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');

return (NULL);
}
