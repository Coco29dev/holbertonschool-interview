#include "search.h"

/**
 * linear_skip - Searches for a value in a sorted skip list, using
 *               the express lane to narrow the range before doing
 *               a bounded linear scan
 * @list: Pointer to the head of the skip list
 * @value: Value to search for
 *
 * Return: Pointer to the first node containing value, or NULL if
 *         value is not found, or if list is NULL
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
    skiplist_t *current, *bound, *temp;

    if (!list)
        return (NULL);

    current = list;
    while (current->express)
    {
        printf("Value checked at index [%lu] = [%d]\n",
               current->express->index, current->express->n);
        if (current->express->n >= value)
            break;
        current = current->express;
    }

    bound = current->express;
    if (!bound)
    {
        bound = current;
        while (bound->next)
            bound = bound->next;
    }
    printf("Value found between indexes [%lu] and [%lu]\n",
           current->index, bound->index);

    temp = current;
    while (temp)
    {
        printf("Value checked at index [%lu] = [%d]\n",
               temp->index, temp->n);
        if (temp->n == value)
            return (temp);
        if (temp->n > value)
            return (NULL);
        temp = temp->next;
    }

    return (NULL);
}
