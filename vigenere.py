# vigenere.py
# Oct 6, 2019
# encrypt messages using Vigenere’s cipher
# encrypting messages using a sequence of keys

import sys
from cs50 import get_string

# //check that only second string AND is alpha only
if len(sys.argv) != 2 or not sys.argv[1].isalpha():
    print("Usage: python vigenere.py k")
    sys.exit(1)

keyword = sys.argv[1]
keylgth = len(keyword)


def shift(c):      # char of keyword, eg A is 0
    if c.isupper():
        return ord(c) - 65
    if c.islower():
        return ord(c) - 97


def rotate(c, k):   # to k-rotate a single chars, skip space
    if c.isupper():
        return chr(((ord(c) - 65 + k) % 26) + 65)   # 65 is 'A'
    elif c.islower():
        return chr(((ord(c) - 97 + k) % 26) + 97)   # 97 is 'a'
    else:
        return c
# function rotate, single char for a to Z will rotate with key
# using c[i] = (p[i] + k) % 26


ptext = get_string("plaintext:  ")
print("ciphertext: ", end="")

j = 0       # ptext[i] counter for only alpha
for i in range(len(ptext)):
    key = shift(keyword[j % keylgth])

    if ptext[i].isalpha():
        print(rotate(ptext[i], key), end='')
        j += 1
    else:
        print(ptext[i], end='')
print()

# $ python vigenere.py ABC
# plaintext:  Hello, world!
# ciphertext: Hfnlp, yosnd!
# $ echo $?
# 0

# $ python vigenere.py bacon
# plaintext:  Meet me at the park at eleven am
# ciphertext: Negh zf av huf pcfx bt gzrwep oz

