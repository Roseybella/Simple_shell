#include "main.h"

/**
 * plus_node - function that adds a new node
 * @head: the head
 * @str: the value of string
 * Return: eachtime, the num
 */

list_t *plus_node(list_t **head, char *str)
{
	list_t *temp;
	list_t *new;

	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);

	new->str = _strdup(str);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}

	new->next = NULL;

	if (!(*head))
	{
		(*head) = new;

		return (new);
	}

	temp = (*head);
	while (temp->next)
		temp = temp->next;

	temp->next = new;
	return (new);
}


/**
 * remove_node - function that remove the node
 * @head: the head
 * @index: the index of node
 * Return: eachtime, (1) if success, (0) if fail
 */

int remove_node(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int w = 0;

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
		if (w == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		w++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * list_strings - function that returns strings
 * @head: the head
 * Return: eachtime, string
 */

char **list_strings(list_t *head)
{
	list_t *node = head;
	size_t w = list_len(head), r;
	char **strs;
	char *str;

	if (!head || !w)
		return (NULL);

	strs = malloc(sizeof(char *) * (w + 1));
	if (!strs)
		return (NULL);

	for (w = 0; node; node = node->next, w++)
	{
		str = _strdup(node->str);

		if (!str)
		{
			for (r = 0; r < w; r++)
				free(strs[r]);
			free(strs);
			return (NULL);
		}

		strs[w] = str;
	}
	strs[w] = NULL;
	return (strs);
}

/**
 * free_link_list - function that frees a linked list
 * @head: the head
 * Return: eachtime (void)
 */

void free_link_list(list_t *head)
{
	list_t *temp;

	if (!head)
		return;

	while (head)
	{
		temp = head->next;
		free(head->str);
		free(head);
		head = temp;
	}
}


/**
 * print_link_list - function that prints a linked list
 * @h: the head
 * Return: eachtime, list
 */

size_t print_link_list(const list_t *h)
{
	char *value;
	size_t numberOfNodes = 0;

	if (!h)
		return (0);

	while (h)
	{
		value = h->str ? h->str : "(nil)";

		printf("%s\n", value);

		h = h->next;
		numberOfNodes++;
	}

	return (numberOfNodes);
}
