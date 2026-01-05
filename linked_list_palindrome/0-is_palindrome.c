#include <stddef.h>
#include "lists.h"

/**
 * reverse_list - reverses a linked list
 * @head: pointer to pointer of first node
 * Return: pointer to first node of reversed list
 */
listint_t *reverse_list(listint_t **head)
{
	listint_t *prev = NULL;
	listint_t *current = *head;
	listint_t *next = NULL;

	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	*head = prev;
	return (*head);
}

/**
 * compare_lists - compares two linked lists
 * @head1: pointer to first list
 * @head2: pointer to second list
 * Return: 1 if lists are identical, 0 otherwise
 */
int compare_lists(listint_t *head1, listint_t *head2)
{
	listint_t *temp1 = head1;
	listint_t *temp2 = head2;

	while (temp1 && temp2)
	{
		if (temp1->n != temp2->n)
			return (0);
		temp1 = temp1->next;
		temp2 = temp2->next;
	}

	if (temp1 == NULL && temp2 == NULL)
		return (1);

	return (0);
}

/**
 * is_palindrome - checks if a singly linked list is a palindrome
 * @head: pointer to pointer of first node of listint_t list
 * Return: 0 if it is not a palindrome, 1 if it is a palindrome
 */
int is_palindrome(listint_t **head)
{
	listint_t *slow, *fast, *prev_slow;
	listint_t *second_half, *middle;
	int result = 1;

	if (*head == NULL || (*head)->next == NULL)
		return (1);

	slow = *head;
	fast = *head;
	prev_slow = *head;
	middle = NULL;

	while (fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		prev_slow = slow;
		slow = slow->next;
	}

	if (fast != NULL)
	{
		middle = slow;
		slow = slow->next;
	}

	second_half = slow;
	prev_slow->next = NULL;
	reverse_list(&second_half);

	result = compare_lists(*head, second_half);

	reverse_list(&second_half);

	if (middle != NULL)
	{
		prev_slow->next = middle;
		middle->next = second_half;
	}
	else
		prev_slow->next = second_half;

	return (result);
}
