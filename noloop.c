// noloop.c  k.c
/* to understand linked node, without using while-loop, and for-loop
*/

#include <stdio.h>
#include <stdlib.h> // malloc

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    // Memory for NUMBERS
    node *NUMBERS = NULL;
    node *ptr_N = NULL;

    node *TempN = malloc(sizeof(node)); if (!TempN) { return 1; }
    TempN->number = 11; // let say Temp2 point address is  22
    TempN->next = NULL;

    NUMBERS = TempN;

    node *Temp2 = malloc(sizeof(node)); if (!Temp2) { return 1; }
    Temp2->number = 22; // let say Temp2 point address is  22
    Temp2->next = NULL;

    ptr_N = NUMBERS;  // same pointer as NUMBERs, ptr_N point to address 11
    ptr_N->next = Temp2; // and now NUMBERS pointing to 'next' contain address 22

    node *Temp3 = malloc(sizeof(node)); if (!Temp3) { return 1; }
    Temp3->number = 33; // let say address is  33
    Temp3->next = NULL;

    ptr_N = ptr_N->next;
    ptr_N->next = Temp3;

    node *Temp4 = malloc(sizeof(node)); if (!Temp4) { return 1; }
    Temp4->number = 23; // let say address is  23
    Temp4->next = NULL;

    ptr_N = ptr_N->next;
    ptr_N->next = Temp4;

    // Print numbers
    for (node *ptr = NUMBERS; ptr != NULL; ptr = ptr->next)
    { printf("%i\n", ptr->number); }

   // Free memory
    node *ptr = NUMBERS; while (ptr != NULL)
    {node *next = ptr->next; free(ptr); ptr = next; }

    printf("so far so good!\n");
}
/*
~/work4/ $ ./k
11
22
33
23
~/work4/ $
*/