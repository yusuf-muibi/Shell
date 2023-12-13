#include "shell.h"

/**
* bfree - Releases a pointer and sets the address to NULL.
* @ptr: Address of the pointer to be freed.
* Return: 1 if freed, 0 otherwise.
*/
int bfree(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
