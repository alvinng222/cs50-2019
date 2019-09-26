// Implements a list of numbers using a linked list

#include <cs50.h>
#include <stdio.h>

typedef struct node
{
    int number;
    struct node *next[3];
}
node;

int main(void)
{
    // Memory for NUMBERS
    node *NUMBERS = NULL; // pointer NUMBERS point to nothing

    // Prompt for NUMBERS (until EOF)
    while (true)
    {
        // Prompt for in_num
        int in_num = get_int("in_num: ");
        // Check for EOF . (ctrl-d)
        if (in_num == INT_MAX) { break; }

        // Allocate space for in_num, ->next = 0x0, ->number = 0
        node *TempN = malloc(sizeof(node)); if (!TempN) { return 1; }

        // temp node
        TempN->number = in_num;  // pointer TempN point to next node number, add in_num
        TempN->next[0] = NULL;      // pointer TempN point to next node next, which is NULL
        if (NUMBERS) // if not null
        {
            // *ptr_N: copy same pointer as NUMBERS, & points to same addresses for number, next
            // ptr_N = ptr_N->next: ptr_N's pointer point to next address of 'next'
            for (node *ptr_N = NUMBERS; ptr_N != NULL; ptr_N = ptr_N->next[0])
            {
                if (!ptr_N->next[0]) // ptr_N->next = NULL
                {
                    ptr_N->next[0] = TempN; // address of 'next' replace with TempN's addresses
                    break;
                }
            }
        }
        else
        {
            //copy TempN pointing addresses into NUMBERS
            NUMBERS = TempN;  // if NUMBERS is NULL
        }
    }
    printf("\n");

    // Print numbers
    for (node *ptr = NUMBERS; ptr != NULL; ptr = ptr->next[0])
    { printf("%i\n", ptr->number); }

    // Free memory
    node *ptr = NUMBERS;
    while (ptr != NULL)
    {
        node *temp = ptr->next[0];
        free(ptr);
        ptr = temp;
    }
}

/*
pointer [NUMBERs] -> node [number, next]. ie addresses of node.number in_num, & node.next = NULL

pointer [TempN] -> node [number, next]. ie addresses of node.number in_num, & node.next = NULL

pointer [ptr_N] -> same addresses of NUMBERS
ptr_N = ptr_N->next: s replaced with 'next' address. ie switch the pointing to 'next' address
*/