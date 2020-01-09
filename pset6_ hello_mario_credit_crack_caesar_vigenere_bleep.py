## CS50 2019 PSET 6  problem

# hello.py
# mario.py
# cash.py
# credit.py
# caesar.py
# crack.py
# vigenère.py
# bleep.py


# https://docs.python.org/3/tutorial/index.html

##### hello.py

# get library for input string
from cs50 import get_string

print("What is your name?")
s = get_string("")

print("Hello, ", s)



##### /more/mario.py
# Oct 3, 2019

from cs50 import get_int

# prompt user for positive number
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# print out the column and rows
for i in range(height):
    for j in range(height):
        # print the space follow by #
        if j < (height - i - 1):
            print(" ", end='')
        else:
            print("#", end='')
        # print return to prompt
    print("  ", end='')

    # print the other half of row
    for k in range(i + 1):
        print("#", end='')
    # print new line
    print()

# $ python mario.py
# Height: -5
# Height: five
# Height: 24
# Height: 4
#    #  #
#   ##  ##
#  ###  ###
# ####  ####



##### cash.py
# Oct 03, 2019

from cs50 import get_float

# Prompt user for input, and convert to cents
while True:
    dollars = get_float("Change owed: ")
    if dollars > 0:
        cents = round(dollars * 100)
        break

cashbal = cents

# using double // to round down for integer
# quarter, 25 cents
qtr_count = cashbal // 25
cashbal = cashbal - (qtr_count * 25)

# dimes 10 cents
dim_count = cashbal // 10
cashbal = cashbal - (dim_count * 10)

# nickels, 5 cents
nic_count = cashbal // 5
cashbal = cashbal - (nic_count * 5)

# pennies, 1 cent
pen_count = cashbal // 1
cashbal = cashbal - (pen_count * 1)

# total cash change
print(qtr_count + dim_count + nic_count + pen_count)

# $ python cash.py
# Change owed: 0.41
# 4



##### credit.py
# Oct 03, 2019

from cs50 import get_int

digit13 = 1000000000000     # visa 13 digits number
digit16 = 1000000000000000  # visa or Master 16 digits number
digit15 = 100000000000000   # Amx 15 digits number


def main():
    # prompt for number between 13 to 17 digits
    while True:
        number = get_int("Number: ")
        if number < (digit16 * 10):
            break

    # if function Luhn valid, check type
    if luhn(number) == 0:
        # Visa uses 13-digit numbers, start with 4. Or
        if number > digit13 and number < (digit13 * 10):
            lastdigit = number // digit13
            if lastdigit == 4:
                print("VISA")
            else:
                print("INVALID")

        # Visa uses 16-digit numbers, start with 4;
        # Master uses 16-digit numbers, start with 51,52,53,54, or 55.
        elif number > digit16 and number < (digit16 * 10):
            lastdigit = number // (digit16 // 10)
            if lastdigit // 10 == 4:
                print("VISA")
            elif lastdigit > 50 and lastdigit < 56:
                print("MASTERCARD")
            else:
                print("INVALID")

        # Amex uses 15-digit numbers, start with 34 or 37
        elif number > digit15 and number < (digit15 * 10):
            lastdigit = number // (digit15 // 10)
            if lastdigit == 37 or lastdigit == 34:
                print("AMEX")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")


def luhn(Num):  # LUHN ALGORITHM, input long number, return with 0 for valid
    counter = 0
    checksum = 0

    # loop and get the remainder by divide by 10, till variable become 0
    while True:
        counter += 1    # start with counter = 1

        # get the first digit by modular 10
        digit1 = Num % 10

        # perform a check for Odd digit or Even digit
        if parity(counter) == 1:
            # if counter is odd, add the 1st digit to checksum
            checksum += digit1
        else:
            # if counter is even, double the digit
            # if more than 9, split digit and add into checksum
            digit2 = digit1 * 2
            if digit2 > 9:
                checksum += (digit2 % 10)   # add 1st digit
                checksum += (digit2 // 10)   # and 2nd digit
            else:
                checksum += digit2

        Num = Num // 10      # next digit
        # print("num", Num)                 # for test

        if Num <= 0:
            # checksum modulus 10
            return checksum % 10


def parity(counter):
    # Check parity of integer
    if counter % 2 == 0:
        return 0
    else:
        return 1


if __name__ == "__main__":
    main()

# $ python credit.py
# 378282246310005 as AMEX
# 5555555555554444 as MASTERCARD
# 4012888888881881 as VISA
# 1234567890 as INVALID



##### caesar.py
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
# $ python caesar.py 1
# plaintext:  Hello World!
# ciphertext: Ifmmp Xpsme!
# $ echo $?
# 0



##### crack.py
# Oct 04, 2019

import sys
import re
import crypt

# Check for correct number of args
if len(sys.argv) != 2 or len(sys.argv[1]) != 13:
    print("Usage: ./crack hash")
    sys.exit(1)

# quatify the 2 chars salt from hash
h = sys.argv[1]     # hash

# The 2 characters in salt must be in the set [./a-zA-Z0-9]
sa = sys.argv[1][0] + sys.argv[1][1]
for c in sa.strip():
    if not re.match(r"[./a-zA-Z0-9]", c):
        exit()

# The characters in keyword only letters
# ap = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcedfghijklmnopqrstuvwxyz"
ap = "amuybep"  # 50CcfIk1QrPr6 > maybe   # for debugging


def decrypt(h, sa):
    for k in range(5):  # 2 chars to 4 chars keywords
        for a in ap:
            for b in ap:
                if k < 3:
                    t = a + b
                    thash = crypt.crypt(t, sa)
                    if h == thash:
                        print(t)
                        return True
                    continue    # skip the c,d loop

                for c in ap:
                    if k < 4:
                        t = a + b + c
                        thash = crypt.crypt(t, sa)
                        if h == thash:
                            print(t)
                            return True
                        continue    # skip the d loop

                    for d in ap:
                        t = a + b + c + d
                        thash = crypt.crypt(t, sa)
                        if h == thash:
                            print(t)
                            return True

    for a in ap:    # 5 chars keywords
        # print("*", end='')  # for debugging.. not immediate!
        for b in ap:
            for c in ap:
                for d in ap:
                    for e in ap:
                        t = a + b + c + d + e
                        thash = crypt.crypt(t, sa)
                        if h == thash:
                            print(t)
                            return True

    return False    # if no result


# function for input of hash,h and salt,sa, return keyword
# to convert into hash from all alpha on chars of keyword, and compare against input, h.
decrypt(h, sa)


# $ python crack.py 51v3Nh6ZWGHOQ
# ROFL
# 502sDZxA/ybHs > puppy
# 50cI2vYkF0YU2 > LOL

#  # Allow alphabetical characters and apostrophes (for possessives)
#     if re.match(r"[A-Za-z]", c) or (c == "'" and index > 0):



##### vigenere.py
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



##### bleep.py
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
# :( handles banned words lists with arbitrary words in them
#     expected "My *** and ***..., not "My cat and dog...

# https://docs.python.org/3/tutorial/index.html


