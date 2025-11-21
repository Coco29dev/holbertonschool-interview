
#include "binary_trees.h"
#include <stdlib.h>

/**
 * heap_size - Calculates the size of the heap
 * @root: Pointer to the root node
 *
 * Return: Size of the heap
 */
size_t heap_size(heap_t *root)
{
	if (root == NULL)
		return (0);

	return (1 + heap_size(root->left) + heap_size(root->right));
}

/**
 * find_parent_by_index - Finds parent node for insertion at specific index
 * @root: Pointer to the root node
 * @index: Index where new node will be inserted
 * @size: Current size of the heap
 *
 * Return: Pointer to the parent node
 */
heap_t *find_parent_by_index(heap_t *root, size_t index, size_t size)
{
	heap_t *parent;
	size_t parent_index;

	if (index == 0)
		return (NULL);

	parent_index = (index - 1) / 2;

	if (parent_index == 0)
		return (root);

	if (parent_index < size / 2)
		parent = find_parent_by_index(root->left, parent_index - 1, size / 2);
	else
		parent = find_parent_by_index(root->right,
				parent_index - size / 2 - 1, size / 2);

	return (parent);
}

/**
 * get_insertion_parent - Gets the parent for the next insertion
 * @root: Pointer to the root node
 *
 * Return: Pointer to the parent node
 */
heap_t *get_insertion_parent(heap_t *root)
{
	size_t size;
	heap_t *queue[1024];
	int front = 0, rear = 0;
	heap_t *current;

	if (!root)
		return (NULL);

	/* Use level-order traversal to find the first node with an empty slot */
	queue[rear++] = root;

	while (front < rear)
	{
		current = queue[front++];

		if (!current->left || !current->right)
			return (current);

		queue[rear++] = current->left;
		queue[rear++] = current->right;
	}

	/* This shouldn't happen in a valid heap */
	size = heap_size(root);
	return (find_parent_by_index(root, size, size));
}

/**
 * swap_values - Swaps values of two nodes
 * @node1: First node
 * @node2: Second node
 */
void swap_values(heap_t *node1, heap_t *node2)
{
	int temp;

	temp = node1->n;
	node1->n = node2->n;
	node2->n = temp;
}

/**
 * heapify_up - Maintains max heap property by moving node up
 * @node: Node to heapify
 */
void heapify_up(heap_t *node)
{
	heap_t *parent;

	if (!node || !node->parent)
		return;

	parent = node->parent;

	if (node->n > parent->n)
	{
		swap_values(node, parent);
		heapify_up(parent);
	}
}

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 * @root: Double pointer to the root node of the Heap
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node, *parent;
	int original_value;

	if (!root)
		return (NULL);

	if (!*root)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}

	parent = get_insertion_parent(*root);

	new_node = binary_tree_node(parent, value);
	if (!new_node)
		return (NULL);

	if (!parent->left)
		parent->left = new_node;
	else
		parent->right = new_node;

	original_value = value;
	heapify_up(new_node);

	/* Find the node with the original value */
	if (new_node->n != original_value)
	{
		/* The value was swapped, find where it ended up */
		heap_t *current = new_node;
		while (current && current->n != original_value)
			current = current->parent;
		if (current)
			return (current);
	}

	return (new_node);
}
