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
#define DICTIONARY "dictionaries/small"

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

    printf("lvl0 "); for (int z = 0; z < N; z++) // ********* .  my test
    { if (root->children[z]) printf("* "); else printf(". ");  } printf("\n");

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
        printf("word: %s: \n", word);
        //printf("1st: %c, 2nd: %c, word: %s  strlen: %lu\n", word[0],word[1], word, strlen(word));
        /*
        *** check the value at childen[i] ???
        call the first alphaber of word
         for next children, check if no same 1st alpha
         placed the 1st alpha to root->children
         if found 1st alpha in children, then ptr = ptr->next

         printf all c
        // TODO */

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
            n->is_word = true;
            n->children[alpha] = NULL;

            if (!ptr->children[alpha])
            {
                ptr->children[alpha] = n;
                //break;
            }

            printf("lvl%i ", i); for (int z = 0; z < N; z++) // ********* .  my test
            { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

            ptr = ptr->children[alpha];

            // TODO


        }
    }

    /*/ Print numbers
    printf("\n");
    for (node *ptr = numbers; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }

    printf("lvl0 "); for (int z = 0; z < N; z++) // ********* .  my test
    { if (root->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");
    */

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
int main(void)
{
    // Memory for numbers
    node *numbers = NULL;

    // Prompt for numbers (until EOF)
    while (true)
    {
        // Prompt for number
        int number = get_int("number: ");

        // Check for EOF
        if (number == INT_MAX)
        {
            break;
        }

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
    }

    // Print numbers
    printf("\n");
    for (node *ptr = numbers; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }

    // Free memory
    node *ptr = numbers;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}

*/