#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;
// Obtain the user's home directory using the _getenv function.
	dir = _getenv(info, "HOME=");
	
    // Check if the "HOME" environment variable exists. If not, return NULL.
	if (!dir)
		return (NULL);
	// Allocate memory for a buffer that will hold the path to the history file.
    // The size of the buffer is calculated as the sum of the lengths of 'dir' and 'HIST_FILE' plus 2 
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	// Check if memory allocation was successful. If not, return NULL.
	if (!buf)
		return (NULL);
	 // Initialize the buffer with a null-terminator.
	buf[0] = 0;
	// Copy the 'dir' string to the buffer using _strcpy.
	_strcpy(buf, dir);
	// Concatenate a '/' character to the buffer using _strcat.
	_strcat(buf, "/");
	// Concatenate the 'HIST_FILE' string to the buffer using _strcat.
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *f_name = get_history_file(info);
	list_t *node = NULL;
// Check if the history file name is valid (not NULL).
	if (!f_name)
		return (-1);
// Attempt to open the history file for writing. The file is created if it doesn't exist, and its content is truncated.
	fd = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	// Free the memory allocated for the history file name.
	free(f_name);
	// If opening the file fails (fd == -1), return an error code.
	if (fd == -1)
		return (-1);
	// Iterate through the list of history commands stored in info->history.
	for (node = info->history; node; node = node->next)
	{
		// Write the command string (node->str) to the file descriptor 'fd' using _putsfd.
		_putsfd(node->str, fd);
		// Append a newline character to separate commands within the file.
		_putfd('\n', fd);
	}
	// Flush the buffer by sending BUF_FLUSH to the file descriptor 'fd'.
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int x, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			build_history_list(info, buf + last, linecount++);
			last = x + 1;
		}
	if (last != x)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *Node = NULL;

	if (info->history)
		Node = info->history;
	add_node_end(&Node, buf, linecount);

	if (!info->history)
		info->history = Node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int z = 0;
// Initialize a pointer 'node' to the head of the history linked list and a counter 'i' to 0.
	while (node)
	{
		// Iterate through the linked list until 'node' is NULL (end of the list).

        // Assign the value of 'i' to the 'num' member of the current 'node'.
		node->num = z++;
		// Move to the next node in the list.
		node = node->next;
	}
	// Return the final value of 'i' as the updated 'info->histcount'.
	return (info->histcount = z);
}
