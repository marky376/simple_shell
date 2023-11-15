#include "shell.h"

/**
 * n_add_node - Adds a node to the start of the list.
 * @head: Address of pointer to the head node.
 * @str: Str field of the new node.
 * @numbs: Node index used by history.
 * Return: Pointer to the newly added node, or NULL on failure.
 */
list_t *n_add_node(list_t **head, const char *str, int numbs)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	n_memset((void *)new_head, 0, sizeof(list_t));

	new_head->num = numbs;
	if (str)
	{
		new_head->str = n_strdup(str);
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
 * n_add_node_end - Adds a node to the end of the list.
 * @head: Address of pointer to the head node.
 * @str: Str field of the new node.
 * @numbs: Node index used by history.
 * Return: Pointer to the newly added node, or NULL on failure.
 */
list_t *n_add_node_end(list_t **head, const char *str, int numbs)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	n_memset((void *)new_node, 0, sizeof(list_t));

	new_node->num = numbs;

	if (str)
	{
		new_node->str = n_strdup(str);
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

/**
 * n_print_list_str - Prints only the 'str' element of a list_t linked list.
 * @head: Pointer to first node
 * Return: Size of the list.
 */
size_t n_print_list_str(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		n_puts(head->str ? head->str : "(nil)");
		n_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * n_delete_node_at_index - Deletes the node at the given index.
 * @head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 * Return: 1 on success, 0 on failure
 */
int n_delete_node_at_index(list_t **head, unsigned int index)
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
 * n_free_list - Frees all nodes of a linked list.
 * @head_ptr: Address of pointer to head node.
 * Return: nothing, void.
 */
void n_free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	node = head;

	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
