#include <stdlib.h>
#include "binary_trees.h"

/**
 * make_avl_node - Creates a new AVL tree node
 * @parent: Pointer to the parent node
 * @value: Value to store in the new node
 *
 * Return: Pointer to the new node, or NULL on failure
 */
avl_t *make_avl_node(avl_t *parent, int value)
{
    avl_t *node;

    node = malloc(sizeof(avl_t));
    if (!node)
        return (NULL);

    node->n = value;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;

    return (node);
}

/**
 * avl_build_recursive - Recursively builds a balanced AVL subtree
 *                        from a sorted array
 * @array: Pointer to the first element of the array
 * @start: Start index of the current subarray
 * @end: End index of the current subarray
 * @parent: Pointer to the parent node of the subtree being built
 *
 * Return: Pointer to the root of the created subtree, or NULL on failure
 */
avl_t *avl_build_recursive(int *array, int start, int end, avl_t *parent)
{
    avl_t *node;
    int mid;

    if (start > end)
        return (NULL);

    mid = (start + end) / 2;

    node = make_avl_node(parent, array[mid]);
    if (!node)
        return (NULL);

    node->left = avl_build_recursive(array, start, mid - 1, node);
    if (start <= mid - 1 && !node->left)
        return (NULL);

    node->right = avl_build_recursive(array, mid + 1, end, node);
    if (mid + 1 <= end && !node->right)
        return (NULL);

    return (node);
}

/**
 * sorted_array_to_avl - Builds an AVL tree from a sorted array
 * @array: Pointer to the first element of the array to convert
 * @size: Number of elements in the array
 *
 * Return: Pointer to the root node of the created AVL tree, or NULL
 *         on failure
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
    if (!array || size == 0)
        return (NULL);

    return (avl_build_recursive(array, 0, (int)size - 1, NULL));
}
