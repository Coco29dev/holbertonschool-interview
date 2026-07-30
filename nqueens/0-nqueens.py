#!/usr/bin/python3
"""Solves the N queens problem."""
import sys


def solve_nqueens(n):
    """Solve the N queens problem and print every solution.

    Args:
        n (int): the size of the board and number of queens.
    """
    board = []  # board[row] = column of the queen placed on that row

    def is_safe(row, col):
        """Check that placing a queen at (row, col) attacks no other."""
        for r in range(row):
            c = board[r]
            if c == col or abs(c - col) == abs(r - row):
                return False
        return True

    def backtrack(row):
        """Place queens row by row using backtracking."""
        if row == n:
            print([[r, board[r]] for r in range(n)])
            return
        for col in range(n):
            if is_safe(row, col):
                board.append(col)
                backtrack(row + 1)
                board.pop()

    backtrack(0)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: nqueens N")
        sys.exit(1)

    try:
        n = int(sys.argv[1])
    except ValueError:
        print("N must be a number")
        sys.exit(1)

    if n < 4:
        print("N must be at least 4")
        sys.exit(1)

    solve_nqueens(n)
