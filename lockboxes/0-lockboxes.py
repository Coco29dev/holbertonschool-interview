#!/usr/bin/python3
"""
Module for solving the lockboxes problem.

This module contains a function to determine if all locked boxes can be opened
given that each box may contain keys to other boxes.
"""


def canUnlockAll(boxes):
    """
    Determine if all boxes can be opened.

    Args:
        boxes (list of lists): List where each index represents a box
                              and contains a list of keys for other boxes.

    Returns:
        bool: True if all boxes can be opened, False otherwise.

    The first box (boxes[0]) is always unlocked initially.
    Each key corresponds to a box number that can be opened.
    """
    if not boxes or len(boxes) == 0:
        return True

    n = len(boxes)
    opened = set([0])
    keys = list(boxes[0])

    while keys:
        key = keys.pop(0)

        if key < n and key not in opened:
            opened.add(key)
            keys.extend(boxes[key])

    return len(opened) == n
