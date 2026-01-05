#!/usr/bin/python3
"""
Log parsing script that reads stdin line by line and computes metrics.
"""
import sys
import signal
import re


def print_statistics(total_size, status_counts):
    """
    Print the computed statistics.
    """
    print(f"File size: {total_size}")
    for status_code in sorted(status_counts.keys()):
        print(f"{status_code}: {status_counts[status_code]}")


def parse_line(line):
    """
    Parse a log line and extract status code and file size.
    Returns (status_code, file_size) or (None, None) if invalid format.
    """
    pattern = (r'^[\d\.]+\s+-\s+\[.+\]\s+"GET /projects/260 HTTP/1\.1"\s+'
               r'(\d+)\s+(\d+)$')
    match = re.match(pattern, line.strip())

    if match:
        status_code = int(match.group(1))
        file_size = int(match.group(2))
        return status_code, file_size
    return None, None


def signal_handler(signum, frame):
    """
    Handle keyboard interruption.
    """
    print_statistics(total_size, status_counts)
    sys.exit(0)


if __name__ == "__main__":
    total_size = 0
    status_counts = {}
    line_count = 0
    valid_status_codes = [200, 301, 400, 401, 403, 404, 405, 500]

    signal.signal(signal.SIGINT, signal_handler)

    try:
        all_lines_count = 0
        for line in sys.stdin:
            all_lines_count += 1
            status_code, file_size = parse_line(line)

            if status_code is not None and file_size is not None:
                total_size += file_size

                if status_code in valid_status_codes:
                    if status_code not in status_counts:
                        status_counts[status_code] = 0
                    status_counts[status_code] += 1

                line_count += 1

                if line_count % 10 == 0:
                    print_statistics(total_size, status_counts)

        if line_count == 0 or line_count % 10 != 0:
            print_statistics(total_size, status_counts)

    except KeyboardInterrupt:
        print_statistics(total_size, status_counts)
        raise
