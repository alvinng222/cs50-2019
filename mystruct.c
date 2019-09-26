/****
    Defining Custom Data Types
****/
// typedef <old name> <new name>

#include <stdio.h>

typedef unsigned char byte;
typedef char *string;

struct car0
{ int year; char *model; };
typedef struct car0 car0_t;

typedef struct car1
{ int year; char *model; }
car1_t;

int main(void)
{
    // variable name declaration
    struct car0 mycar3;
    // field assessing
    mycar3.year = 1976;
    mycar3.model = "Datsun";

    car1_t mycar4;
    mycar4.year = 1976;
    mycar4.model = "Datsun";

    printf("\n");
}