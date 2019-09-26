/* f.c
    fread fscanf ok, but got repeat word

*/

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
bool unload(void);

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

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    char word[LENGTH + 1];
    node *temp = malloc(sizeof(node)); *temp = *root;



    // Insert words into trie
    char *wn[5];
    // Buffer for a word
    for (int k=0; k<5; k++)
    {
        wn[k] = malloc(sizeof(word));
    }

    //int fscanf(FILE *stream, const char *format, ...);
    while (fscanf(file, "%s %s %s %s %s", wn[0], wn[1], wn[2], wn[3], wn[4]) != EOF)
    {
        for (int q = 0; q<5; q++)
        {
            printf("%s ", wn[q]);
            //TODO

        }
        printf("***\n");

        // ** need to break for repeated word
    }
    printf("\n");


    // free malloc
    for (int k=0; k<5; k++)
    {
        free(wn[k]);
    }
    free(temp);
    free(root);

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
/*
    // Buffer for a word
    char word0[LENGTH + 1], word1[LENGTH + 1], word2[LENGTH + 1],
    word3[LENGTH + 1], word4[LENGTH + 1];

    // Insert words into trie
    //int fscanf(FILE *stream, const char *format, ...);
    while (fscanf(file, "%s %s %s %s %s", word0, word1, word2, word3, word4) != EOF)
    {   printf("%s %s %s %s %s\n", word0, word1, word2, word3, word4 );
        // need to break for ""
        //break; // while break if less than 5 word
    } */
/*
     // fread ( <buffer> , <size>, <qty>, ptr )
     printf("sizeof word: %lu\n", sizeof(word));

    char *Tbuffer = malloc(sizeof(word) *1);
    fread (Tbuffer, sizeof(word), 1, file);

    for (int i = 0; i < 46; i++)
    {   printf("%c",Tbuffer[i]);
    }
    printf("\n"); */