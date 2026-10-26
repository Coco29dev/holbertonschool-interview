#!/usr/bin/python3
"""Rain module"""


def rain(walls):
    """Return the total amount of rainwater retained between the walls"""
    if not walls:
        return 0

    left = 0
    right = len(walls) - 1
    left_max = 0
    right_max = 0
    total = 0

    while left < right:
        if walls[left] < walls[right]:
            if walls[left] >= left_max:
                left_max = walls[left]
            else:
                total += left_max - walls[left]
            left += 1
        else:
            if walls[right] >= right_max:
                right_max = walls[right]
            else:
                total += right_max - walls[right]
            right -= 1

    return total
