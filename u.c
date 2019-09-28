/* status: add unload free root
==4089==
==4089== 224 bytes in 1 blocks are still reachable in loss record 2 of 2
==4089==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==4089==    by 0x422500: load (u.c:41)
==4089==    by 0x426076: main (u.c:389)
copied 'load' from after dictionary6.c
copied node by created temp at function load */
// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen
#include "dictionary.h"
// Default dictionary
#define DICTIONARY "dictionaries/cat"
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


/***** ***** ***** load */
// Loads dictionary into memory, returning true if successful else false
/*  for every dictionary word, iterate through the trie
    each element in children corresponds to a
    different letter
    check the value at childen[i]
        if NULL, malloc a new node, have children[i] point to it
        if not NULL, move to new node and continue
    if at end of word, set is_word to true */
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));        // valgrind fail here
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

    // Buffer for a word
    char word[LENGTH + 1];

    node *temp = malloc(sizeof(node));
    *temp = *root;
    //free (temp);

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        //printf("word: %s: \n", word); // ****

        node *ptr = root;
        for ( int i = 0, l = strlen(word); i<l; i++)
        {
            // n - 97 integer of alphabet, which coressponding to children[n]
            int a = (int)word[i] - 97;
            if (a == -58) { a = 26;} //  apostrophes, 39,

            if (!ptr->children[a])
            {
                // Allocate space for new node
                node *n = malloc(sizeof(node));
                if (!n) {return 1; }        // timing same, if remove
                *n = *temp; // copy the format only

                //ptr->is_word = true; // set this pointer to true (1) for every node reached
                ptr->children[a] = n;
                //printf("B");
                //break;
            }

            ptr = ptr->children[a]; // next ptr
        }

        // if at end of word, set is_word to true
        ptr->is_word = true;
    }

    free(temp);

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}



// Unloads dictionary from memory, returning true if successful else false
/* # unload
* unload from bottom to top
* travel to lowest possiblt node
* * free all pointers in children
* * backtrack upwards, freeing all elements in
* * each children array until you hit root node
* recursion!
# valgrind
valgrind --v --leak-check=full austinpowers.txt*/
// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    /**** cat only *******
    bool scanning;          // bool scanning = scanline(0,50);

    node *ml[46];           // memorise the address at this level
    int   ma[46];             // memorise the alphabetic of that level
    int   mc = 0;             // levelth
    int    a = 0;              // alpha position

    node *ptr = root;           ml[0] = ptr; ma[0] = 2 ;
    ptr = ptr->children[ma[0]]; ml[1] = ptr; ma[1] = 0 ;  // found  'c'
    ptr = ptr->children[ma[1]]; ml[2] = ptr; ma[2] = 19; // found 'a'
    ptr = ptr->children[ma[2]]; ml[3] = ptr; ma[3] = 4 ; // found 't'
    ptr = ptr->children[ma[3]]; // ml[4] = ptr; // 'e'

    scanning = scanline(0,50);
    //FREE MEMORY  ptr = previous;
    ptr = ml[2]; ptr->children[ma[2]] = NULL; free (ml[3]);
    ptr = ml[1]; ptr->children[ma[1]] = NULL; free (ml[2]);
    ptr = ml[0]; ptr->children[ma[0]] = NULL; free (ml[1]); //bool

    scanning = scanline(0,50);

    return false;

    // good! no error
    ******/

    //bool scanning;
    //bool scanning = scanline(0,5);

    node *ml[46];           // memorise the address at this level
    int ma[46];             // memorise the alphabetic of that level

    node *ptr = root;       // copy pointer

    int mc = 0;             // levelth
    int a = 0;              // alpha position

    while (a < 27)
    {
        if (ptr->children[a] != NULL)
        {                   //printf("w lvl %i %c\n", mc,  97+a);// testing *
            ml[mc] = ptr;   // save the pointer at mc level
            ma[mc] = a;     // save the alpha position at mc level
                                                //printf("m%i ", mc);
            // point to the next children
            ptr = ptr->children[a]; //same as ptr = ml[mc]->children[ma[mc]];
            mc++;           // next deeper level
            a=0;            // start to scan at alpha 0
        }
        else
        {
            a++;                                // if the children null, move to next alpha

            while (a >= 27)
            {                                   //printf("N lvl %i %c\n", mc,  97+a); // testing *
                node *temp = ptr;
                mc = mc -1;                     // move back to the previous level
                if (mc < 0) { break; }          // if already at root level, break

                // copy pointer and alpha to pointer
                ptr = ml[mc];                   //printf("ml[%i]  |  ", mc); //previous , t
                ptr->children[ma[mc]] = NULL;   //printf("children[ma[%i] %c = null |  ", mc, ma[mc]+97 );

                if (temp != NULL)
                                                //printf("free ml[%i + 1] \n",mc);

                { free (temp); }

                a = ma[mc]+1;   // if a is 26, loop back
            }
        }
    }

    //return n;
    // for testing
    //printf("%i N:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
    //{ if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");
    free (root);
    //bool scanning = scanline(0,5);

    return true;
    // valgrind error  for cat and catch, 3 block loss at malloc, u.c:353

}

/*
    // Free memory
    node *ptr = numbers;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
*/



// Returns number of words in dictionary if loaded else 0 if not yet loaded
/*  1. use array for alpha[] and lvl[] for 45+1 levels of "pneumonoultramicroscopicsilicovolcanoconiosis"
    2. check is_word, scan and save alpha & pointer's add if not NULL, then go to next level pointer's add
    3. is scan all NULL, back to -1 level and +1 alpha */
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
        {                   //printf("w lvl %i %c\n", mc,  97+a);// testing *
            ml[mc] = ptr;   // save the pointer at mc level
            ma[mc] = a;     // save the alpha position at mc level

            // point to the next children
            ptr = ptr->children[a]; //same as ptr = ml[mc]->children[ma[mc]];
            mc++;           // next deeper level
            a=0;            // start to scan at alpha 0

            if ((ptr->is_word) == true )    // if word is true, count
            {
                n++;        //printf("TRUE\n");
            }
        }
        else
        {
            // if the children null, move to next alpha
            a++;

            while (a >= 27)
            {               //printf("N lvl %i %c\n", mc,  97+a); // testing *
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



// Scan print of node from root to bottom, only for mine debugging
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


int main(void)
{
    bool loaded = load(DICTIONARY);

    /*/ bool check(const char *word) //Print word if misspelled
    const char *word = "Cat";
    bool misspelled = !check(word);
    if (misspelled) {printf("");}else{printf("Yes! good!\n");} */

    //unsigned int n = size(); printf("Total words: %i\n", n);

    bool unloaded = unload();
    //bool scanline(int sc_low, int sc_max)
    //bool scanning = scanline(0,50);
}

/*

valgrind --leak-check=full --show-leak-kinds=all ./u

*/