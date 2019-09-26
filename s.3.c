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


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //1. use array for alpha[] and lvl[] for 45+1 levels of "pneumonoultramicroscopicsilicovolcanoconiosis"
    //2. check is_word, scan and save alpha & pointer's add if not NULL, then go to next level pointer's add
    //3. is scan all NULL, back to -1 level and +1 alpha
    //4. if +1 alpha > 27, -1 level, return fault if already at root.
    //5. goto 2
    //4. if will never reach max lvl, else return fault.

    int n = 0; // word count

    node *ml[46]; // memorise the address at this level
    int ma[46]; // memorise the alphabetic of that level

    node *ptr = root;

    int mc = 0; // levelth
    int a = 0;
    while (a < 27)
    {
        if (ptr->children[a] != NULL)
        {
                    printf("lvl %i ", mc);
                    printf("%i w:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
                    { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

                                        //printf("%c ", a+97);
                                        //printf("\nSAVING lv %i: %c | :  ",mc, a+97);
            ml[mc] = ptr;
            ma[mc] = a;
                                        //printf(" level %i: %c | ",mc, ma[mc]+97);

            ptr = ptr->children[a]; //same as ptr = ml[mc]->children[ma[mc]];
            mc++; a=0;

            if ((ptr->is_word) == true ) // if word is true, count
            {
                printf("TRUE\n");
                n++;}
        }
        else
        {
            a++;                        //printf("+"); //printf("%c", a+97);

            if (a >= 27)
            {
                    printf("lvl %i ", mc);
                    printf("%i N:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
                    { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

                mc = mc -1; if (mc < 0) {printf("BREAK1!"); break;}
                ptr = ml[mc]; a = ma[mc]+1; //// if a is 26, ir BREAK !!

                if (a == 27)
                {mc = mc -1; if (mc < 0) {printf("BREAK2!"); break;}
                ptr = ml[mc]; a = ma[mc]+1;}

                                        //printf("\nback to %C: ",ma[mc]+97 );
                                        //printf("lv %i: %c | ",mc, ma[mc]+97);

                                        //printf("ma[mc] : "); for (int i = 0; i < 5; i++) { printf("%c ", ma[i]+97 ); } printf("\n");
            }
        }
    }

    //printf(" level 0: %c | \n", ma[0]+97);
    //printf(" level 1: %c | \n", ma[1]+97);
    return n;
}
/*
printf("%i p:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
{ if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");
*/
/*
while (ptr->children[a] == NULL)
    {
        a++;
    }

    ml[mc] = ptr;
    ma[mc] = a;

    ptr = ml[mc]->children[ma[mc]];
    mc++;

*/
/*
    // Print numbers
    printf("\n");
    for (node *ptr = numbers; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }
*/




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


    // KIV
    printf(" >>>>> unloading >>>>> \n");
    int test = 0; // for testing

    int a = 0;
    node *ptr = root;
    node *t;

    while (a < 27)
    {
        //printf("%i ", a);
        test++ ; if (test >300) break;  // ******

        if (ptr -> children[a] != NULL)
        {
            t = ptr;
                printf("%i t: ", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
                { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

            ptr = ptr -> children[a];
                printf("%i p: ", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
                { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

            //if (ptr->is_word == false)
            //{printf("break if \n"); ptr = t;}

            a = 0;

            //printf("\n");
        }
        else
        { a ++;
            /* if (a > 26)
            {
                a = 0;
                printf("\n b: "); for (int z = 0; z < N; z++) // ********* .  my test
                { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

                free (ptr);
                ptr = t;

                //break;
            }*/
        }
    }

    return false;
}
/*
           //printf("not null ");
            node *t = ptr -> children[a];
            if (t -> is_word == true)
            {
           //printf("not null ");
            node *t = ptr -> children[a];
            if (t -> is_word == true)
            {
printf("lvl? "); for (int z = 0; z < N; z++) // ********* .  my test
                { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");
*/

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
        printf("word: %s: \n", word); // ****

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



int main(void)
{
    bool loaded = load(DICTIONARY);

    /*/ bool check(const char *word) //Print word if misspelled
    const char *word = "Cat";
    bool misspelled = !check(word);
    if (misspelled) {printf("");}else{printf("Yes! good!\n");} */

    unsigned int n = size(); printf("Total words: %i\n", n);

    //bool unloaded = unload();
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