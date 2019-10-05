# crack.py
# Oct 04, 2019

import sys
import crypt

# Check for correct number of args
if len(sys.argv) != 2 or len(sys.argv[1]) != 13:
    print("Usage: ./crack hash")
    sys.exit(1)

# quatify the 2 chars salt from hash
h = sys.argv[1]     # hash

# The 2 characters in salt must be in the set [./a-zA-Z0-9]
sa = sys.argv[1][0] + sys.argv[1][1]
slib = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./"
if sa in slib:
    print(end='')       # ?? print nothing

# The characters in keyword only letters
ap = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcedfghijklmnopqrstuvwxyz"
# ap = "amaybez" # 50CcfIk1QrPr6 > maybe   # for debugging


def decrypt(h, sa):
    for z in ap:    # 2 chars keywords
        for y in ap:
            t = z + y
            thash = crypt.crypt(t, sa)
            if h == thash:
                return t
    for z in ap:    # 3 chars keywords
        for y in ap:
            for x in ap:
                t = z + y + x
                thash = crypt.crypt(t, sa)
                if h == thash:
                    return t
    for z in ap:    # 4 chars keywords
        # print(".", end='')      # for debugging
        for y in ap:
            for x in ap:
                for w in ap:
                    t = z + y + x + w
                    thash = crypt.crypt(z + y + x + w, sa)
                    if h == thash:
                        return t
    for z in ap:    # 5 chars keywords
        # print("*", end='')      # for debugging
        for y in ap:
            # print(".", end='')  # for debugging
            for x in ap:
                for w in ap:
                    for v in ap:
                        t = z + y + x + w + v
                        thash = crypt.crypt(z + y + x + w + v, sa)
                        if h == thash:
                            return t
# decrypt(h, sa)
# function for input of hash,h and salt,sa, return keyword
# to convert into hash from all alpha on chars of keyword, and compare against input, h.


print(decrypt(h, sa))


# $ python crack.py 51v3Nh6ZWGHOQ
# ROFL

