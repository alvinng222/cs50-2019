/******
CS50-2019 pset 4 tries
video by Zamyla

TRIES
=====

# Tries
* every node contains an array of node pointers
* * one for every letter in the alphabet + " \' "
* * each element in the array points to another node
* * * if that node is NULL, then that letter isn't the next letter of any word in that sequence
* every node indicates whether it's the last character of a word

typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;
node *root;


# load
* for every dictionary word, iterate through the trie
* each element in children corresponds to a different letter
* check the value at childen[i]
* * if NULL, malloc a new node, have children[i] point to it
* * if not NULL, move to new node and continue
* if at end of word, set is_word to true

# check
* case-insensitivity
* assume strings with only alphabeticall characters and/or apostrophes

# traversing a trie
* for each letter in inout word
* * go to corresponding element in children
* * * if NULL, word is misspelled
* * * if not NULL, move to next letter
* * once at end of input word
* * * check if is_word is true

# freeing linked lists
node *cursor = head;
while (cursor != NULL)
{
    node *temp = cursor;
    cursor = cursor -> next;
    free(temp);
}

# unload
* unload from bottom to top
* travel to lowest possiblt node
* * free all pointers in children
* * backtrack upwards, freeing all elements in
* * each children array until you hit root node
* recursion!

# valgrind
valgrind --v --leak-check=full austinpowers.txt

# tips
* pass in a smaller dictionary
* * usuage: ./speller [dictionary] text
* * default: large
* * also try: small
* * make your own!
* pen and paper!


staff's solution
~cs50/2019/x/pset4/speller dictionaries/large texts/lalaland.txt
 MISSPELLED:     955
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        17756
TIME IN load:         0.02
TIME IN check:        0.01
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.04

staff's solution
~cs50/2019/x/pset4/speller dictionaries/large texts/shakespeare.txt
WORDS MISSPELLED:     45691
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        904612
TIME IN load:         0.02
TIME IN check:        0.60
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.63

staff's solution
~cs50/2019/x/pset4/speller dictionaries/large texts/grimm.txt
WORDS MISSPELLED:     718
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        103614
TIME IN load:         0.02
TIME IN check:        0.06
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.08

*****/

