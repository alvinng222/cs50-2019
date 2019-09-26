// link3.c
/*
to understand link w Tries list
create node for 3 datas + its add

place datas together

*/

#include <stdio.h>
#include <stdlib.h> // malloc

typedef struct link3
{
    int item;
    struct link3 *boxA;
    struct link3 *boxB;
    struct link3 *boxC;
}
link3;

//link3 *root;

int main(void)
{
    //link3 *root = NULL;  // memory not allocated, still can run

    link3 *root = malloc(sizeof(link3)); if (!root) { return 1; }
    root -> item = 9;

    // Allocate space for in_num, ->next = 0x0, ->number = 0
    link3 *tmpA = malloc(sizeof(link3)); if (!tmpA) { return 1; }
    tmpA -> item = 11;


    root -> boxA = tmpA;


    // tmpA = NULL;
    //root -> boxA = tmpA;
    //link3 *tmpB = NULL;
    //root -> boxB = tmpB;


    //tmpB -> item = 12;
    printf("so far so good!\n");
}

/*
// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

typedef struct node
{
    int number;
    struct node *next;
}
node;


*/