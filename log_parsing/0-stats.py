#!/usr/bin/python3
"""Log parsing script."""

import sys


def print_stats(total_size, status_counts):
    """Prints the current statistics."""
    print("File size: {}".format(total_size))
    for code in sorted(status_counts.keys(), key=int):
        if status_counts[code] != 0:
            print("{}: {}".format(code, status_counts[code]))


if __name__ == "__main__":
    total_size = 0
    valid_codes = ["200", "301", "400", "401", "403", "404", "405", "500"]
    status_counts = {code: 0 for code in valid_codes}
    line_count = 0

    try:
        for line in sys.stdin:
            parts = line.split()

            try:
                size = int(parts[-1])
                total_size += size
            except (IndexError, ValueError):
                pass

            try:
                status = parts[-2]
                if status in status_counts:
                    status_counts[status] += 1
            except IndexError:
                pass

            line_count += 1
            if line_count % 10 == 0:
                print_stats(total_size, status_counts)

    except KeyboardInterrupt:
        print_stats(total_size, status_counts)
        raise

    print_stats(total_size, status_counts)
