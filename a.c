/* status : test on load: fread fscanf
to improve loading speed - KIV
copied unload from dictionary.c
copied load from u.3.c, copied scanline from scan.c, a.c from d.5
*/
// Implements a dictionary's functionality

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

// my prototype
bool scanline(int sc_low, int sc_max);


    /***** load *****/
bool load(const char *dictionary) // simplified version
{
    root = malloc(sizeof(node));    if (root == NULL)   {return false;   }
    root->is_word = false;  for (int i = 0; i < N; i++) {root->children[i] = NULL;   }
    // Open dictionary
    FILE *file = fopen(dictionary, "r");    if (file == NULL)   {unload();  return false;   }
    char word[LENGTH + 1];

    node *temp = malloc(sizeof(node)); *temp = *root;

    // Insert words into trie, with 5 buffers
    char *wn[5];
    // Buffer for a word
    for (int k=0; k<5; k++)
    {   wn[k] = malloc(sizeof(word));
    }

    //int fscanf(FILE *stream, const char *format, ...);
    while (fscanf(file, "%s %s %s %s %s", wn[0], wn[1], wn[2], wn[3], wn[4]) != EOF)
    {
        for (int q = 0; q<5; q++)
        {
            printf("%s ", wn[q]);
            //TODO
            node *ptr = root;
            for ( int i = 0, l = strlen(wn[q]); i<l; i++)        // time
            {
                int a = (int)wn[q][i] - 97;
                if (a == -58) { a = 26;}                        // time

                if (!ptr->children[a])                          // time
                {
                    node *n = malloc(sizeof(node)); //if (!n) {return 1; } // same timing
                    *n = *temp;

                    ptr->children[a] = n;
                }
                ptr = ptr->children[a]; // next ptr
            }
            ptr->is_word = true;

            }
            // ** need to break for repeated word
    }

    // free malloc
    for (int k=0; k<5; k++)
    {
        free(wn[k]);
    }

    free (temp);
    fclose(file); // Close dictionary
    return true; // Indicate success
}


    /***** UNLOAD *****/
// Unloads dictionary from memory, returning true if successful else false // u.c
bool unload(void)
{   //bool scanning = scanline(0,5)
    node *ml[46];  int ma[46];  // memorise the alphabetic of that level
    node *ptr = root;       // copy pointer
    int mc = 0; int a = 0;  // levelth // alpha position
    while (a < 27)
    {   if (ptr->children[a] != NULL)
        {   ml[mc] = ptr; ma[mc] = a; // save the pointer, alpha at mc level
            ptr = ptr->children[a]; // point to the next children
            mc++; a=0;      // next deeper level// start to scan at alpha 0
        }
        else
        {   a++;                                // if the children null, move to next alpha
            while (a >= 27)
            {   node *temp = ptr;
                mc = mc -1;if (mc < 0) { break; } // move back to the previous level,root level, break
                ptr = ml[mc];   // copy pointer and alpha to pointer
                ptr->children[ma[mc]] = NULL;
                if (temp != NULL) { free (temp); }
                a = ma[mc]+1;   // if a is 26, loop back
            }
        }
    }
    //bool scanning = scanline(0,5);
    return true;
}


    /***** scanline *****/
// Scan print of node from root to bottom, only for mine debugging // scan.c
bool scanline(int sc_low, int sc_max)
{
    if (root == NULL) return false; // if root not created
    printf("scanline sc _ level alpha is_word: children + alpha\n");
    int sc = 0; // scanline count.. can adjust sc_low & sc_max

    node *ml[46];           // memorise the address at this level
    int ma[46];             // memorise the alphabetic of that level

    node *ptr = root;       // copy pointer

    int mc = 0;             // levelth
    int a = 0;              // alpha position
    while (a < 27)
    {
        if (ptr->children[a] != NULL)
        {
            if (sc >= sc_low)
            {
                printf("%i _%2i %c %i: ",sc,mc,97+a,ptr->is_word);
                for (int z = 0; z < N; z++) // 0 is false**** my test
                { if (ptr->children[z]) printf("%c ", 97+z); else printf(". "); } printf("\n");
            }
            sc++; if (sc>sc_max ) {printf(" exit sc_max = %i\n", sc_max);return false; }

            ml[mc] = ptr;   // save the pointer at mc level
            ma[mc] = a;     // save the alpha position at mc level

            // point to the next children
            ptr = ptr->children[a]; //same as ptr = ml[mc]->children[ma[mc]];
            mc++;           // next deeper level
            a=0;            // start to scan at alpha 0
        }
        else
        {
            // if the children null, move to next alpha
            a++;
            while (a >= 27)
            {
                mc = mc -1;                 // move back to the previous level
                if (mc < 0)                 // if already at root level, break
                {
                    break;
                }
                ptr = ml[mc];   // copy pointer and alpha to pointer
                a = ma[mc]+1;   // if a is 26, loop back
            }
        }
    }
    return true;
}


    /***** MAIN *****/
int main(void)
{
    bool loaded = load(DICTIONARY); bool scanning = scanline(0,5);
    printf("so far so good!\n");

    bool unloaded = unload();  //scanning = scanline(0,5);
}

/***** *****/