# bleep.py
# Oct 7, 2017
# Implement a program that censors messages that contain
# words that appear on a list of supplied "banned words."

# my algorithm
# load the text from babbed.txt, into set()
# for word in text
#  strcomp?? for ord in dict
#   if found replace with '*' * len(word)

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

    # print("words",words)

    print("What message would you like to censor?")
    text = get_string("")

    stext = text.split()
    # print("stext",stext)

    for txt in stext:
        if txt.lower() in words:
            print("*" * len(txt), end=' ')
        else:
            print(txt, end=' ')

    print()
    #pass


# def check(word):
#     """Return true if word is in dictionary else false"""
#     return word.lower() in words


def load(dictionary):
    """Load dictionary into memory, returning true if successful else false"""
    file = open(dictionary, "r")
    for line in file:
        words.add(line.rstrip("\n"))
    file.close()
    return True

    # TODO

if __name__ == "__main__":
    main()

# Odds are you’ll find str.split of interest.

# Odds are you’ll find str.lower of interest.

# Odds are you’ll find str.strip of interest,
# to chomp off any trailing newlines that may be
# attached to words on your "banned words" list.



# $ ~cs50/2019/x/pset6/bleep banned.txt

# ~/ $ ~cs50/2019/x/pset6/bleep
# Usage: python bleep.py dictionary

# $ python bleep.py banned.txt
# What message would you like to censor?
# What the heck
# What the ****
# $ python bleep.py banned.txt
# What message would you like to censor?
# gosh darn it
# **** **** it

# https://docs.python.org/3/tutorial/index.html
