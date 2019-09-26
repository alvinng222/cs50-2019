// load cat
// free cat


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen
//#include "dictionary.h"

// Default dictionary
//#define DICTIONARY "dictionaries/small"

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

#include <stdio.h>

unsigned int size(void);

int main(void)
{
   int C_mallloc = 0;  // **** tobedel ****
    // Initialize trie
    root = malloc(sizeof(node));                        C_mallloc++;  // **** tobedel ****
    if (root == NULL) { return false; }
    root->is_word = false;
    for (int i = 0; i < N; i++) { root->children[i] = NULL; }

                    printf("%i p:",root->is_word); for (int z=0; z<N;z++) // 0 is false**** my test
                    {if(root->children[z]) printf("%c ",97+z); else printf(". ");} printf("\n");

    // Insert words into trie
    char *word = "cat";
        node *ptr = root;
        for ( int i = 0, l = strlen(word); i<l; i++)
        {
            int alpha = (int)word[i] - 97; if (alpha == -58) { alpha = 26;}

            // Allocate space for new node
            node *n = malloc(sizeof(node));         C_mallloc++;  // **** tobedel ****
            if (!n) {return 1; }

                    printf("%i p:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
                    { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

            // Add alpha to list
            n->is_word = false; n->children[alpha] = NULL;

            if (!ptr->children[alpha]) { ptr->children[alpha] = n; }
            ptr = ptr->children[alpha]; // next ptr
        ptr->is_word = true;
    }

    printf("* Count malloc: %i \n",C_mallloc++);  // **** tobedel ****

    unsigned int n = size(); printf("Total words: %i\n", n);
}
/*
string names[enrollment];
    string dorms[enrollment];

struct car
{ int year; char model[10]; }
typedef struct car car_t;
    char *a = "azAZ'";
    printf("%c = %i \n", a[0], (int)a[0]);
    printf("%c = %i \n", a[1], (int)a[1]);
    printf("%c = %i \n", a[2], (int)a[2]);
    printf("%c = %i \n", a[3], (int)a[3]);
    printf("%c = %i \n", a[4], (int)a[4]);
*/

//convert to print all level
unsigned int size(void)
{
    int n = 0;              // word count

    node *ml[46];           // memorise the address at this level
    int ma[46];             // memorise the alphabetic of that level

    node *ptr = root;       // copy pointer

    int mc = 0;             // levelth
    int a = 0;              // alpha position
    while (a < 27)
    {
        if (ptr->children[a] != NULL)
        {                   printf("w lvl %i %c\n", mc,  97+a);// testing *
            ml[mc] = ptr;   // save the pointer at mc level
            ma[mc] = a;     // save the alpha position at mc level

            // point to the next children
            ptr = ptr->children[a]; //same as ptr = ml[mc]->children[ma[mc]];
            mc++;           // next deeper level
            a=0;            // start to scan at alpha 0

            if ((ptr->is_word) == true )    // if word is true, count
            {
                n++;        printf("TRUE\n");
            }
        }
        else
        {
            // if the children null, move to next alpha
            a++;

            while (a >= 27)
            {               printf("N lvl %i %c\n", mc,  97+a); // testing *
                mc = mc -1;                 // move back to the previous level

                if (mc < 0)                 // if already at root level, break
                {
                    break;
                }

                // copy pointer and alpha to pointer
                ptr = ml[mc];
                a = ma[mc]+1;   // if a is 26, loop back
            }
        }
    }

    return n;
    /* for testing
    printf("%i N:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
    { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");  */
}

bool load(const char *dictionary)
{   // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)   {return false;}
    root->is_word = false;
    for (int i = 0; i < N; i++) {root->children[i] = NULL;}

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)   {unload();   return false;}

    // Buffer for a word
    char word[LENGTH + 1];

    node *temp = malloc(sizeof(node));  *temp = *root;

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {   node *ptr = root;
        for ( int i = 0, l = strlen(word); i<l; i++)
        {   int a = (int)word[i] - 97;
            if (a == -58) { a = 26;} //  apostrophes, 39,

            if (!ptr->children[a])
            {   node *n = malloc(sizeof(node)); if (!n) {return 1; } *n = *temp;

                ptr->children[a] = n;
            }
            ptr = ptr->children[a]; // next ptr
        }
        ptr->is_word = true;
    }
    free (temp);
    fclose(file);   // Close dictionary
    return true;    // Indicate success
}
