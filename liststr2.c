#include "shell.h"

/**
 * list_len - determines length of linked_list
 * @h: pointer to first node
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t z = 0; 

	while (h)
	{
		h = h->next;// Move to the next node in the list.
		z++;// Increment the counter for each element.
	}
	return (z);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;// Check if the linked list is empty, or if the number of elements is zero, and return NULL.
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;// Set the last element of the array to NULL to indicate the end of the array.
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0)); // Print the integer 'num'.
		_putchar(':'); // Print a colon.
		_putchar(' '); // Print a space.
		_puts(h->str ? h->str : "(Null)");// Print NULL.
		_puts("\n");// Print a newline character to separate entries.
		h = h->next;// Move to the next node in the list.
		x++;// Increment the counter for each element printed.
	}
	return (x);// Return the total number of elements printed.
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c))) // If the string starts with the prefix and matches the character (or character check is not required), return the current node.
			return (node);
		node = node->next;// Move to the next node in the list.
	}
	return (NULL);// If no matching node is found, return NULL.
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t x = 0; // Initialize an index counter to keep track of the position of the target node.

	while (head)
	{
		if (head == node) // Check if the current node matches the target node.
			return (x); // If a match is found, return the index 'x'.
		head = head->next; // Move to the next node in the list.
		x++;// Increment the index counter for each node visited.
	}
	return (-1);
}
