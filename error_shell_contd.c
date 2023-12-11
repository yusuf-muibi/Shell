#include "shell.h"

/**
* _custom_atoi - converts a string to an integer
* @s: the string to be converted
* Return: 0 if no numbers in string
*/
int _custom_atoi(char *s)
{
int i = 0;
unsigned long int result = 0;

if (*s == '+')
s++;  /* TODO: why does this make main return 255? */
for (i = 0; s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
result *= 10;
result += (s[i] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}

/**
* print_error_message - prints an error message
* @shell_info: the parameter & return info struct
* @error_str: string containing specified error type
* Return: Nothing
*/
void print_error_message(info_t *shell_info, char *error_str)
{
print_error_string(shell_info->fname);
print_error_string(": ");
print_decimal(shell_info->line_count, STDERR_FILENO);
print_error_string(": ");
print_error_string(shell_info->argv[0]);
print_error_string(": ");
print_error_string(error_str);
}

/**
* print_decimal - function prints a decimal (integer) number (base 10)
* @input: the input
* @fd: the file descriptor to write to
* Return: number of characters printed
*/
int print_decimal(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int i, count = 0;
unsigned int absolute_value, current;

if (fd == STDERR_FILENO)
__putchar = print_error_char;

if (input < 0)
{
absolute_value = -input;
__putchar('-');
count++;
}
else
absolute_value = input;

current = absolute_value;
for (i = 1000000000; i > 1; i /= 10)
{
if (absolute_value / i)
{
__putchar('0' + current / i);
count++;
}
current %= i;
}

__putchar('0' + current);
count++;

return (count);
}

/**
* convert_to_string - converter function, a clone of itoa
* @num: number
* @base: base
* @flags: argument flags
* Return: string
*/
char *convert_to_string(long int num, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';
}

array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do {
*--ptr = array[n % base];
n /= base;
} while (n != 0);

if (sign)
*--ptr = sign;

return (ptr);
}

/**
* erase_comments - function replaces first instance of '#' with '\0'
* @buf: address of the string to modify
*
* Return: Always 0;
*/
void erase_comments(char *buf)
{
int i;

for (i = 0; buf[i] != '\0'; i++)
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
