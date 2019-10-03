# caesar.py
# Oct 03, 2019

from cs50 import get_string
import sys

# Check for correct number of args
if len(sys.argv) != 2 or not sys.argv[1].isdecimal():
    print("Usage: ./caesar key")
    sys.exit(1)

key = int(sys.argv[1])


def rotate(p, k):
    for i in p:
        if i.isupper():
            print(chr(((ord(i) - 65 + k) % 26) + 65), end="")   # 65 is 'A'
        elif i.islower():
            print(chr(((ord(i) - 97 + k) % 26) + 97), end='')   # 97 is 'a'
        else:
            print(i, end="")
# function rotate, single char for a to Z will rotate with key
# using c[i] = (p[i] + k) % 26


ptext = get_string("plaintext:  ")
print("ciphertext: ", end="")
rotate(ptext, key)
print()

# ASCII to alpha use ord , chr
# For example, ord('a') returns the integer 97.
# chr() is the inverse.

# ~/pset6/caesar/ $ python caesar.py
# Usage: ./caesar key
# ~/pset6/caesar/ $ echo $?
# 1
# ~/pset6/caesar/ $ python caesar.py 3
# plaintext:  BARFOO
# ciphertext: EDUIRR
# ~/pset6/caesar/ $ echo $?
# 0
