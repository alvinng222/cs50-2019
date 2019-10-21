# cs50-2019 helper.py
# Oct 14, 2019

def lines(a, b):
    """Return lines in both a and b"""
    # TODO

    # Python strings support methods
    # https://docs.python.org/3/library/stdtypes.html#string-methods
    m = a.splitlines()
    n = b.splitlines()
    matched = []    # Space for matched

    for x in m:
        for y in n:
            if x == y:
                if x not in matched:
                    matched.append(x)
    return matched
    # https://docs.python.org/3/tutorial/datastructures.html


def sentences(a, b):
    """Return sentences in both a and b"""
    # TODO

    from nltk.tokenize import sent_tokenize
    m = sent_tokenize(a)
    n = sent_tokenize(b)
    matched = []    # Space for matched

    for x in m:
        for y in n:
            if x == y:
                if x not in matched:
                    matched.append(x)
    return matched
    # https://www.nltk.org/api/nltk.tokenize.html


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    # TODO

    ms = []
    for u in range(len(a)-n+1):
        ms.append(a[u:u + n])

    ns = []
    for u in range(len(b)-n+1):
        ns.append(b[u:u + n])

    matched = []
    for x in ms:
        for y in ns:
            if x == y:
                if x not in matched:
                    matched.append(x)
    return matched


# ./compare --sentences inputs/LittlePrince_HowardTranslation.txt inputs/LittlePrince_WoodsTranslation.txt
# "Goodbye," said the fox.

# ./compare --substrings 3 a1.txt a2.txt