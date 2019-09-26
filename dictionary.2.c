// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

// Loads dictionary into memory, returning true if successful else false
/*
* for every dictionary word, iterate through the trie
* each element in children corresponds to a different letter
* check the value at childen[i]
* * if NULL, malloc a new node, have children[i] point to it
* * if not NULL, move to new node and continue
* if at end of word, set is_word to true
*/
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }


    //printf("%i r:", root->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
    //{ if (root->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        //printf("word: %s: \n", word); // ****

        node *ptr = root;
        for ( int i = 0, l = strlen(word); i<l; i++)
        {
            // n - 97 integer of alphabet, which coressponding to children[n]
            int alpha = (int)word[i] - 97;
            if (alpha == -58) { alpha = 26;} //  apostrophes, 39,

            // Allocate space for new node
            node *n = malloc(sizeof(node));
            if (!n) {return 1; }

            // Add alpha to list
            n->is_word = false;
            n->children[alpha] = NULL;

            if (!ptr->children[alpha])
            {
                //ptr->is_word = true; // set this pointer to true (1) for every node reached
                ptr->children[alpha] = n;
                //printf("B");
                //break;
            }

            //printf("%i t:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
            //{ if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

            ptr = ptr->children[alpha]; // next ptr
            //printf("%i p:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
            //{ if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");
        }

        // if at end of word, set is_word to true
        ptr->is_word = true;
        //printf("%i e:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
        //{ if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");
    }

    /*/ Print numbers
    printf("\n");
    for (node *ptr = numbers; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }
    */

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Returns true if word is in dictionary else false
/*  # check
* case-insensitivity
* assume strings with only alphabeticall characters and/or apostrophes
    # traversing a trie
* for each letter in inout word
* * go to corresponding element in children
* * * if NULL, word is misspelled
* * * if not NULL, move to next letter
* * once at end of input word
* * * check if is_word is true
*/
// eg ~/work4/ $ ./speller texts/wordsworth.txt
bool check(const char *word)
{
    node *ptr = root;

    //printf("here we are: %s\n", word);
    int length = strlen(word);
    for (int c=0; c<length; c++)
    {
        int alpha;
        // check if word[] is captitalize; a = 97, z = 122,  A = 65 , Z = 90 , ' = 39
        if ((word[c] >= 'A') && (word[c] <= 'Z'))
        {alpha = (int)word[c] +32 - 97;}

        else
        // n - 97 integer of alphabet, which coressponding to children[n]
        {alpha = (int)word[c] - 97;}

        if (alpha == -58) { alpha = 26;} //  apostrophes, 39,

        // if NULL at the dictionary
        if (ptr -> children[alpha] == NULL)
        {
            return 0; // 0 is false
        }

        // pointer to next letter
        ptr = ptr -> children[alpha];
    }
    //printf("\n");

    // if at end of word, check is_word to true
    if (ptr->is_word == true) return 1;

    return false;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
