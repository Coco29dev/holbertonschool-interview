#include <stdio.h>
#include "search_algos.h"

/**
 * print_array - prints the array being searched
 * @array: pointer to the first element
 * @size: number of elements
 */
void print_array(int *array, size_t size)
{
	size_t i;

	printf("Searching in array: ");
	for (i = 0; i < size; i++)
		printf("%d%s", array[i], i < size - 1 ? ", " : "\n");
}

/**
 * search_rec - recursively finds the first index of value
 * @array: pointer to the first element
 * @size: number of elements
 * @value: value to search for
 * @offset: index of array[0] in the original array
 *
 * Return: index of the first occurrence, or -1
 */
int search_rec(int *array, size_t size, int value, size_t offset)
{
	size_t mid;

	if (size == 0)
		return (-1);
	print_array(array, size);
	mid = (size - 1) / 2;
	if (array[mid] < value)
		return (search_rec(array + mid + 1, size - mid - 1, value,
				   offset + mid + 1));
	if (array[mid] == value)
	{
		if (mid == 0 || array[mid - 1] != value)
			return ((int)(offset + mid));
		return (search_rec(array, mid + 1, value, offset));
	}
	return (search_rec(array, mid, value, offset));
}

/**
 * advanced_binary - searches for the first occurrence of value in a
 * sorted array using binary search
 * @array: pointer to the first element
 * @size: number of elements
 * @value: value to search for
 *
 * Return: index of the first occurrence, or -1
 */
int advanced_binary(int *array, size_t size, int value)
{
	if (array == NULL)
		return (-1);
	return (search_rec(array, size, value, 0));
}
