#!/usr/bin/python3
"""Recursively count keywords in the hot article titles of a subreddit."""
import requests


def count_words(subreddit, word_list, after=None, counts=None):
    """Print a sorted count of keywords found in hot article titles.

    Args:
        subreddit: name of the subreddit to query.
        word_list: list of keywords (case-insensitive).
        after: pagination token for the next page (internal use).
        counts: dictionary of accumulated counts (internal use).
    """
    if counts is None:
        counts = {}
        for word in word_list:
            counts[word.lower()] = 0
    url = "https://www.reddit.com/r/{}/hot.json".format(subreddit)
    headers = {"User-Agent": "linux:count_it:v1.0 (by /u/holberton_student)"}
    params = {"limit": 100, "after": after}
    response = requests.get(url, headers=headers, params=params,
                            allow_redirects=False)
    if response.status_code != 200:
        return
    try:
        data = response.json().get("data", {})
    except ValueError:
        return
    for child in data.get("children", []):
        title = child.get("data", {}).get("title", "").lower().split()
        for word in counts:
            counts[word] += title.count(word)
    after = data.get("after")
    if after is not None:
        return count_words(subreddit, word_list, after, counts)
    # Duplicates in word_list must be summed.
    totals = {}
    for word in word_list:
        key = word.lower()
        totals[key] = counts[key] * word_list_count(word_list, key)
    results = sorted(((w, c) for w, c in totals.items() if c > 0),
                     key=lambda item: (-item[1], item[0]))
    for word, count in results:
        print("{}: {}".format(word, count))


def word_list_count(word_list, key):
    """Return how many times key appears in word_list (case-insensitive)."""
    return [w.lower() for w in word_list].count(key)
