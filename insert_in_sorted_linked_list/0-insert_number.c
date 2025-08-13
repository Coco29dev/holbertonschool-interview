#include <stdlib.h>
#include "lists.h"

/**
 * insert_node - Inserts a number into a sorted singly linked list
 * @head: Double pointer to the head of the list
 * @number: Number to insert
 *
 * Return: Address of the new node, or NULL if it failed
 */
listint_t *insert_node(listint_t **head, int number)
{
    listint_t *new_node, *current;

    /* vérification que head est valide */
    if (head == NULL)
        return (NULL);

    /* allocation de mémoire pour new node */
    new_node = malloc(sizeof(listint_t));
    if (new_node == NULL)
        return (NULL);

    /* initiaisation de new node */
    new_node->n = number;
    new_node->next = NULL;

    /* cas 1: insérer en début de liste si : */
    /* - la liste est vide */
    /* - la valeur est >= au premier élément */
    if (*head == NULL || (*head)->n >= number)
    {
        new_node->next = *head;
        *head = new_node;
        return (new_node);
    }

    /* recherche de la position dans la liste */
    /* cherche le last node dont la valeur est < à 'number' */
    current = *head;
    while (current->next != NULL && current->next->n < number)
        current = current->next;

    /* insertion du new node */
    /* entre 'current' et 'current->next' */
    new_node->next = current->next;
    current->next = new_node;

    return (new_node);
}
