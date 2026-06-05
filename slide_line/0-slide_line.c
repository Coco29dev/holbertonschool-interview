#include <stddef.h>
#include "slide_line.h"

static void slide_left(int *line, size_t size)
{
    size_t i, pos;

    /* Step 1: compacter vers la gauche */
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

    /* Step 2: fusionner */
    for (i = 0; i + 1 < size; i++)
    {
        if (line[i] != 0 && line[i] == line[i + 1])
        {
            line[i] *= 2;
            line[i + 1] = 0;
            i++;
        }
    }

    /* Step 3: re-compacter */
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

static void slide_right(int *line, size_t size)
{
    size_t i, pos;

    if (size == 0)
        return;

    /* Step 1: compacter vers la droite */
    pos = size - 1;
    i = size;
    while (i > 0)
    {
        i--;
        if (line[i] != 0)
        {
            line[pos] = line[i];
            if (pos != i)
                line[i] = 0;
            if (pos > 0)
                pos--;
        }
    }

    /* Step 2: fusionner de droite à gauche */
    i = size;
    while (i > 1)
    {
        i--;
        if (line[i] != 0 && line[i] == line[i - 1])
        {
            line[i] *= 2;
            line[i - 1] = 0;
            i--;
        }
    }

    /* Step 3: re-compacter vers la droite */
    pos = size - 1;
    i = size;
    while (i > 0)
    {
        i--;
        if (line[i] != 0)
        {
            line[pos] = line[i];
            if (pos != i)
                line[i] = 0;
            if (pos > 0)
                pos--;
        }
    }
}

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
