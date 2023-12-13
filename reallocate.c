#include "shell.h"

/**
* _memset - Sets a constant byte in a memory area.
* @s: Pointer to the memory area.
* @b: The byte to fill the memory area with.
* @m: Number of bytes to be filled.
* Return: A pointer to the memory area s.
*/
char *_memset(char *s, char b, unsigned int m)
{
unsigned int i;

for (i = 0; i < m; i++)
s[i] = b;
return (s);
}

/**
* ffree - Releases memory allocated for a string of strings.
* @pp: The string of strings.
*/
void ffree(char **pp)
{
char **a = pp;

if (!pp)
return;
while (*pp)
free(*pp++);
free(a);
}

/**
* _realloc - Reallocates a memory block.
* @ptr: Pointer to the previous dynamically allocated block.
* @old_size: Original byte size of the block.
* @new_size: Desired byte size of the new block.
* Return: Pointer to the resized block.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *p;

if (!ptr)
return (malloc(new_size));
if (!new_size)
return (free(ptr), NULL);
if (new_size == old_size)
return (ptr);

p = malloc(new_size);
if (!p)
return (NULL);

old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
p[old_size] = ((char *)ptr)[old_size];
free(ptr);
return (p);
}
