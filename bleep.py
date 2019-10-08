# bleep.py
# Oct 7, 2017
# Implement a program that censors messages that contain
# words that appear on a list of supplied "banned words."

from cs50 import get_string
from sys import argv

# Default dictionary
WORDS = "banned.txt"

# Words in dictionary
words = set()


def main():

    # Check for correct number of args
    if len(argv) != 2:
        print("Usage: python bleep.py dictionary")
        exit(1)

    loaded = load(WORDS)
    # Exit if dictionary not loaded
    if not loaded:
        print(f"Could not load {WORDS}.")
        exit(1)

    print("What message would you like to censor?")
    text = get_string("")

    stext = text.split()    # convert to set of words

    for t in stext:
        if t.lower() in words:
            print("*" * len(t), end=' ')
        else:
            print(t, end=' ')
    print()


def load(dictionary):
    """Load dictionary into memory, returning true if successful else false"""
    file = open(dictionary, "r")
    for line in file:
        words.add(line.rstrip("\n"))
    file.close()
    return True
    # pass


if __name__ == "__main__":
    main()


# $ python bleep.py banned.txt
# What message would you like to censor?
# What the heck
# What the ****
# $ python bleep.py banned.txt
# What message would you like to censor?
# gosh darn it
# **** **** it

# https://docs.python.org/3/tutorial/index.html

# :( handles banned words lists with arbitrary words in them
#     expected "My *** and ***..., not "My cat and dog...