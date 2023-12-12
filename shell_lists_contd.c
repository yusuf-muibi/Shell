#include "shell.h"

/**
* get_list_size - determines size of linked list
* @current_node: pointer to current node
* Return: size of list
*/
size_t get_list_size(const list_t *current_node)
{
size_t list_size = 0;

while (current_node)
{
current_node = current_node->next;
list_size++;
}
return (list_size);
}

/**
* list_to_str_array - returns an array of strings from the list's data
* @head_node: pointer to head node
* Return: array of strings
*/
char **list_to_str_array(list_t *head_node)
{
list_t *nodes = head_node;
size_t list_size = get_list_size(head_node), i;
char **strings_array;
char *string;

if (!head_node || !list_size)
return (NULL);

strings_array = malloc(sizeof(char *) * (list_size + 1));
if (!strings_array)
return (NULL);

for (list_size = 0; nodes; nodes = nodes->next, list_size++)
{
string = malloc(_strlen(nodes->string) + 1);
if (!string)
{
for (i = 0; i < list_size; i++)
free(strings_array[i]);
free(strings_array);
return (NULL);
}

string = _strcpy(string, nodes->string);
strings_array[list_size] = string;
}
strings_array[list_size] = NULL;
return (strings_array);
}

/**
* display_list - prints all elements of a list_t linked list
* @current_node: pointer to current node
* Return: size of list
*/
size_t display_list(const list_t *current_node)
{
size_t list_size = 0;

while (current_node)
{
_puts(convert_to_string(current_node->index, 10, 0));
_putchar(':');
_putchar(' ');
_puts(current_node->string ? current_node->string : "(nil)");
_puts("\n");
current_node = current_node->next;
list_size++;
}
return (list_size);
}

/**
* find_matching_node - returns node whose data starts with prefix
* @node: pointer to list head
* @prefix: string to match
* @next_char: the next character after prefix to match
* Return: matching node or NULL
*/
list_t *find_matching_node(list_t *node, char *prefix, char next_char)
{
char *match_ptr = NULL;

while (node)
{
match_ptr = starts_with(node->string, prefix);
if (match_ptr && ((next_char == -1) || (*match_ptr == next_char)))
return (node);
node = node->next;
}
return (NULL);
}

/**
* get_node_position - gets the position of a node
* @head_node: pointer to list head
* @node: pointer to the target node
* Return: position of node or -1
*/
ssize_t get_node_position(list_t *head_node, list_t *node)
{
size_t position = 0;

while (head_node)
{
if (head_node == node)
return (position);
head_node = head_node->next;
position++;
}
return (-1);
}
