#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head) // Check if the head pointer is NULL and return NULL if it is.
		return (NULL);
	new_head = malloc(sizeof(list_t)); // Allocate memory for a new node.
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num; // Set the 'num' field of the new node to the provided 'num' value.
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}


size_t print_list_str(const list_t *h)
{
	size_t x = 0; // Initialize a counter to keep track of the number of elements.

	while (h)
	{
		_puts(h->str ? h->str : "(Null)"); // Print the string or "(Null)" if it's NULL.
		_puts("\n"); // Print a newline character to separate entries.
		h = h->next; // Move to the next node in the list.
		x++; // Increment the counter for each element printed.
	}
	return (x); // Return the total number of elements printed.
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *h;

	if (!head_ptr || !*head_ptr)
		return;
	h = *head_ptr; // Get a reference to the head of the linked list.
	node = h;
	while (node)
	{
		next_node = node->next; // Get the next node in the list.
		free(node->str); / Free the memory associated with the string stored in the current node.
		free(node); // Free the memory associated with the current node.
		node = next_node; // Move to the next node in the list.
	}
	*head_ptr = NULL; // Set the head pointer to NULL to indicate that the list is now empty.
}
