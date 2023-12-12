#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@destination: the pointer to the memory area
 *@byte: the byte to fill *destination with
 *@size: the amount of bytes to be filled
 *Return: (destination) a pointer to the memory area destination
 */
char *_memset(char *destination, char byte, unsigned int size)
{
unsigned int i;

for (i = 0; i < size; i++)
destination[i] = byte;
return (destination);
}

/**
* ffree - frees an array of strings
* @string_array: array of strings
*/
void ffree(char **string_array)
{
char **current = string_array;

if (!string_array)
return;
while (*string_array)
free(*string_array++);
free(current);
}

/**
* _realloc - reallocates a block of memory
* @pointer: pointer to previous malloc'ated block
* @old_size: byte size of previous block
* @new_size: byte size of new block
* Return: pointer to the old block nameen.
*/
void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size)
{
char *new_pointer;

if (!pointer)
return (malloc(new_size));
if (!new_size)
return (free(pointer), NULL);
if (new_size == old_size)
return (pointer);

new_pointer = malloc(new_size);
if (!new_pointer)
return (NULL);

old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
new_pointer[old_size] = ((char *)pointer)[old_size];
free(pointer);
return (new_pointer);
}
