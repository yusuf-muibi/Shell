#include "shell.h"

/**
 * free_and_nullify - frees a pointer and sets the address to NULL
 * @pointer_address: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_and_nullify(void **pointer_address)
{
if (pointer_address && *pointer_address)
{
free(*pointer_address);
*pointer_address = NULL;
return (1);
}
return (0);
}
