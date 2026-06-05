#include <stddef.h>
#include "slide_line.h"

/**
 * slide_left - Slides and merges the array to the left
 * @line: Pointer to the array of integers
 * @size: Number of elements in the array
 */
static void slide_left(int *line, size_t size)
{
    size_t i, pos;

    /* Step 1: compacter (retirer les zéros) */
    pos = 0;
    for (i = 0; i < size; i++)
    {
        if (line[i] != 0)
        {
            line[pos] = line[i];
            if (pos != i)
                line[i] = 0;
            pos++;
        }
    }

    /* Step 2: fusionner les voisins identiques */
    for (i = 0; i + 1 < size; i++)
    {
        if (line[i] != 0 && line[i] == line[i + 1])
        {
            line[i] *= 2;
            line[i + 1] = 0;
            i++; /* sauter le suivant déjà fusionné */
        }
    }

    /* Step 3: re-compacter après fusion */
    pos = 0;
    for (i = 0; i < size; i++)
    {
        if (line[i] != 0)
        {
            line[pos] = line[i];
            if (pos != i)
                line[i] = 0;
            pos++;
        }
    }
}

/**
 * slide_right - Slides and merges the array to the right
 * @line: Pointer to the array of integers
 * @size: Number of elements in the array
 */
static void slide_right(int *line, size_t size)
{
    size_t i, pos;

    /* Step 1: compacter vers la droite */
    pos = size - 1;
    for (i = size; i > 0; i--)
    {
        if (line[i - 1] != 0)
        {
            line[pos] = line[i - 1];
            if (pos != i - 1)
                line[i - 1] = 0;
            pos--;
        }
    }

    /* Step 2: fusionner de droite à gauche */
    for (i = size - 1; i > 0; i--)
    {
        if (line[i] != 0 && line[i] == line[i - 1])
        {
            line[i] *= 2;
            line[i - 1] = 0;
            i--; /* sauter le précédent déjà fusionné */
        }
    }

    /* Step 3: re-compacter vers la droite après fusion */
    pos = size - 1;
    for (i = size; i > 0; i--)
    {
        if (line[i - 1] != 0)
        {
            line[pos] = line[i - 1];
            if (pos != i - 1)
                line[i - 1] = 0;
            pos--;
        }
    }
}

/**
 * slide_line - Slides and merges an array of integers
 * @line: Pointer to the array of integers
 * @size: Number of elements in the array
 * @direction: Direction to slide (SLIDE_LEFT or SLIDE_RIGHT)
 *
 * Return: 1 on success, 0 on failure
 */
int slide_line(int *line, size_t size, int direction)
{
    if (direction == SLIDE_LEFT)
    {
        slide_left(line, size);
        return (1);
    }
    if (direction == SLIDE_RIGHT)
    {
        slide_right(line, size);
        return (1);
    }
    return (0);
}
