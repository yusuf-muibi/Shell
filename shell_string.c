#include "shell.h"

/**
* _strlen - returns the length of a string
* @str: the string whose length to check
* Return: integer length of string
*/
int _strlen(char *str)
{
int length = 0;

if (!str)
return (0);

while (*str++)
length++;
return (length);
}

/**
*str_compare - performs lexicographic comparison of two strings.
* @s1: the first string
* @s2: the second string
* Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/
int str_compare(char *s1, char *s2)
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
* starts_with - checks if needle starts with haystack
* @haystack: string to search
* @needle: the substring to find
* Return: address of next char of haystack or NULL
*/
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}

/**
* string_concat - concatenates two strings
* @destination: the destination buffer
* @source: the source buffer
* Return: pointer to destination buffer
*/
char *string_concat(char *destination, char *source)
{
char *result = destination;

while (*destination)
destination++;
while (*source)
*destination++ = *source++;
*destination = *source;
return (result);
}
