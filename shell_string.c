#include "shell.h"
/**
* _strlen - Computes the length of a string.
* @s: The string whose length to check.
* Return: Integer length of the string.
*/
int _strlen(char *s)
{
int i = 0;
if (!s)
return (0);
while (*s++)
i++;
return (i);
}
/**
* _strcmp - Compares two strings lexicographically.
* @s1: The first string.
* @s2: The second string.
* Return: Negative if s1 is less than s2,
*         Positive if s1 is greater than s2,
*         Zero if s1 is equal to s2.
*/
int _strcmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}
/**
* starts_with - Checks if the needle starts with the haystack.
* @haystack: String to search.
* @needle: The substring to find.
* Return: Address of the next character in haystack or NULL.
*/
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}
/**
* strcat_custom - Concatenates two strings into a single string.
* @dest: The destination buffer to store the concatenated strings.
* @src: The source buffer containing the string to be appended.
* Return: A pointer to the destination buffer with the concatenated strings.
*/
char *_strcat(char *dest, char *src)
{
char *ret = dest;
while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}
