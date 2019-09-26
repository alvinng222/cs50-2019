// scan.c Sep23,2019
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

int main(void)
{
    node *l[46];

    root = malloc(sizeof(node)); if (root == NULL) {return false;}
    root->is_word = false;for (int i = 0; i < N; i++) { root->children[i] = NULL; }

    node *ptr = root;
    ptr->is_word = false;
    l[0] = ptr;

    l[1] = malloc(sizeof(node));
    l[1]->is_word = false;
    l[1]->children[0] = NULL;
    //free (l[1]); bool scanning = scanline(0,50); // zero error here
    ptr->children[2] = l[1]; // l[0]->children[2] 'c' // 27 error on scanning
    //ptr->children[2] = NULL; free (l[1]); bool scanning = scanline(0,50); // zero error here
    ptr = ptr->children[2];
     //ptr = l[0]; ptr->children[2] = NULL; free (l[1]); bool scanning = scanline(0,50);// zero error here

    l[2] = malloc(sizeof(node));
    l[2]->is_word = false;
    l[2]->children[19] = NULL;
    //free (l[2]);ptr = l[0]; ptr->children[2] = NULL; free (l[1]); bool scanning = scanline(0,50);// zero error here
    ptr->children[0] = l[2]; // l[1]->children[0] 'a'
    ptr = ptr->children[0];

    l[3] = malloc(sizeof(node));
    l[3]->is_word = false;
    l[3]->children[4] = NULL;
    ptr->children[19] = l[3]; // l[1]->children[0] 'e'
    ptr = ptr->children[19];

    //FREE MEMORY  ptr = previous;
    ptr = l[2]; ptr->children[19] = NULL;free (l[3]);
    ptr = l[1]; ptr->children[0] = NULL;free (l[2]);
    ptr = l[0]; ptr->children[2] = NULL; free (l[1]); bool scanning = scanline(0,50);
    // YES zero error


    //bool scanning = scanline(0,50);
}
/*
            Allocate space for new node
            node *n = malloc(sizeof(node));
            n->is_word = false;
            n->children[alpha] = NULL;
            ptr->children[alpha] = n;
            ptr = ptr->children[alpha]; // next ptr

    printf("%i r:", root->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
    { if (root->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");
*/

// Scan print of node from root to bottom, only for debugging
bool scanline(int sc_low, int sc_max)
{
    if (root == NULL) return false;
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

/* with scanning
ok
scanline sc _ level alpha is_word: children + alpha
==6166==
==6166== HEAP SUMMARY:
==6166==     in use at exit: 256 bytes in 2 blocks
==6166==   total heap usage: 2 allocs, 0 frees, 256 bytes allocated
==6166==
==6166== LEAK SUMMARY:
==6166==    definitely lost: 0 bytes in 0 blocks
==6166==    indirectly lost: 0 bytes in 0 blocks
==6166==      possibly lost: 0 bytes in 0 blocks
==6166==    still reachable: 256 bytes in 2 blocks
==6166==         suppressed: 0 bytes in 0 blocks
==6166== Reachable blocks (those to which a pointer was found) are not shown.
==6166== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==6166==
==6166== For counts of detected and suppressed errors, rerun with: -v
==6166== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/
/*
   ptr->is_word = true;
    ptr = ptr->children[2];

    root = malloc(sizeof(node));  C_mallloc++;  // **** tobedel ****
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }
*/
