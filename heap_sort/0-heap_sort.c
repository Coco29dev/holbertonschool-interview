#include "sort.h"

/**
 * swap - swaps two integers and prints the array
 * @array: the array
 * @size: full size of the array, used for printing
 * @a: index of the first element
 * @b: index of the second element
 */
void swap(int *array, size_t size, size_t a, size_t b)
{
	int tmp;

	tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
	print_array(array, size);
}

/**
 * sift_down - restores the max heap property from a given root
 * @array: the array
 * @size: full size of the array, used for printing
 * @root: index of the root to sift down
 * @end: size of the heap
 */
void sift_down(int *array, size_t size, size_t root, size_t end)
{
	size_t largest, left, right;

	while (1)
	{
		largest = root;
		left = 2 * root + 1;
		right = left + 1;
		if (left < end && array[left] > array[largest])
			largest = left;
		if (right < end && array[right] > array[largest])
			largest = right;
		if (largest == root)
			return;
		swap(array, size, root, largest);
		root = largest;
	}
}

/**
 * heap_sort - sorts an array of integers in ascending order
 * using the sift-down heap sort algorithm
 * @array: the array to sort
 * @size: number of elements in the array
 */
void heap_sort(int *array, size_t size)
{
	size_t i;

	if (!array || size < 2)
		return;
	for (i = size / 2; i > 0; i--)
		sift_down(array, size, i - 1, size);
	for (i = size - 1; i > 0; i--)
	{
		if (array[0] != array[i])
			swap(array, size, 0, i);
		sift_down(array, size, 0, i);
	}
}
