#include <math.h>
#include <stdio.h>
#include "menger.h"

/**
 * is_hole - Checks if position (x, y) is in a hole of the Menger sponge
 * @x: Column index
 * @y: Row index
 *
 * Return: 1 if it's a hole, 0 otherwise
 */
static int is_hole(int x, int y)
{
    while (x > 0 || y > 0)
    {
        if (x % 3 == 1 && y % 3 == 1)
            return (1);
        x /= 3;
        y /= 3;
    }
    return (0);
}

/**
 * menger - Draws a 2D Menger Sponge
 * @level: Level of the Menger Sponge
 */
void menger(int level)
{
    int size, x, y;

    if (level < 0)
        return;

    size = (int)pow(3, level);

    for (y = 0; y < size; y++)
    {
        for (x = 0; x < size; x++)
        {
            if (is_hole(x, y))
                printf(" ");
            else
                printf("#");
        }
        printf("\n");
    }
}
