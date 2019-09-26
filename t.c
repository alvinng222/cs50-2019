// Implements a dictionary's functionality
/*
# load
* for every dictionary word, iterate through the trie
* each element in children corresponds to a different letter
* check the value at childen[i]
* * if NULL, malloc a new node, have children[i] point to it
* * if not NULL, move to new node and continue
* if at end of word, set is_word to true

each word will contain only lowercase alphabetical characters and possibly apostrophes,
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen
#include "dictionary.h"

// Default dictionary
#define DICTIONARY "dictionaries/medium"

// Represents number of children for each node in a trie
#define N 27 // 26 letters + apostrophes ??

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

    for (int i = 0; i < N; i++) // ********* .  my test
    { if (root->children[i]) printf("trure ! "); else printf("false ! ");  } printf("\n");


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
        printf("word: %s: ", word);
        //printf("1st: %c, 2nd: %c, word: %s  strlen: %lu\n", word[0],word[1], word, strlen(word));
        /*
        *** check the value at childen[i] ???
        call the first alphaber of word
         for next children, check if no same 1st alpha
         placed the 1st alpha to root->children
         if found 1st alpha in children, then ptr = ptr->next

         printf all c
        // TODO */

        for (int i = 0, l = strlen(word); i<l; i++)
        {
            // n - 97 integer of alphabet, which coressponding to children[n]
            // each word will contain only lowercase alphabetical characters and possibly apostrophes, 39,
            int a = (int)word[i];
            printf("%c %i |", word[i], a);

            // Allocate space for number
            node *n = malloc(sizeof(node));
            if (!n) { return 1; }

            // Add number to list
            n->is_word = true;
            //n->children[i] = NULL;

            //root = n;
            root->children[i]  = n;
            //if (root->children[i]) printf("TRUE !");


        }
        printf("\n");

        /*
        // Allocate space for number
        node *n = malloc(sizeof(node));
        if (!n)
        {
            return 1;
        }

        // Add number to list
        n->number = number;
        n->next = NULL;
        if (numbers)
        {
            for (node *ptr = numbers; ptr != NULL; ptr = ptr->next)
            {
                if (!ptr->next)
                {
                    ptr->next = n;
                    break;
                }
            }
        }
        else
        {
            numbers = n;
        }
        */
    }

    for (int i = 0; i < N; i++) // ********* .  my test
    { if (root->children[i]) printf("trure ! "); else printf("false ! ");  } printf("\n");

    // Print root
    //for (node *ptr = numbers; ptr != NULL; ptr = ptr->next)
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        node *ptr = root;
        ptr = ptr->children[i];
        if (root->is_word == false)
        {
            printf("i: %i False | ", i);
        }
        else
        printf("i: %i True | ", i);
    }
    printf("\n");


    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}

int main(void)
{
    bool loaded = load(DICTIONARY);
    printf("so far so good!\n");
}
