#include "shell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;
 // Check if the input string is NULL
	if (!str)
		return;
	
    // Iterate through the characters in the string until a null terminator '\0' is reached.

	while (str[i] != '\0')
	{       // Call a function "_eputchar" to output each character one by one.
		_eputchar(str[i]);
		// Increment the index to move to the next character in the string.
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{ // Check if the character should trigger a buffer flush or if the buffer is full.
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{   // If a flush is triggered or the buffer is full, write the contents of the buffer to file descriptor 2 (typically stderr).
		write(2, buf, a);
		// Reset the buffer index 'i' to 0 for the next set of characters.
		a = 0;
	}
	// If the character is not a flush trigger, store it in the buffer and increment the buffer index.
        if (c != BUF_FLUSH)
	
		buf[a++] = c;
	// Return 1 to indicate that the character has been successfully processed.
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

    // Check if the character should trigger a buffer flush or if the buffer is full.
	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{       // If a flush is triggered or the buffer is full, write the contents of the buffer to the specified file descriptor 'fd'.
		write(fd, buf, a);
		// Reset the buffer index 'a' to 0 for the next set of characters.
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int x = 0;
// Check if the input string is NULL.
	if (!str)
		return (0);
	
    // Iterate through the characters in the string until a null terminator '\0' is reached.
	while (*str)
	{
		x += _putfd(*str++, fd);
	}
	return (x);
}
