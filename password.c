//password.c
/*
Assume that each password is no longer than five (5) characters. Gasp!
Assume that each password is composed entirely of alphabetical characters (uppercase and/or lowercase).
*/
// loop around all alphabet from A till ZZZZZ, till match with crypt hash

#include <crypt.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h> //strlen

char *combi_2c(char x, char y);

char *hash = "50cI2vYkF0YU2";
char *salt = "50";
char *alpha = "ABCD";

int main(void)
{
    // for 3 char type
    int an = strlen(alpha);
    for (int c1 = 0; c1 < an; c1++)
    {
        for (int c2 = 0; c2 < an; c2++)
        {
            for (int c3 = 0; c3 < an; c3++)
            {   
            printf("%c%c%c ", alpha[c1], alpha[c2], alpha[c3]);
            }
        }
    }
    printf("still thinking!\n");
}

// function to combine 2 char into string//
// need to check for memory leak
char *combi_2c(char x, char y)
{
    // Allocate memory for another string
    char *t = malloc((2 + 1) * sizeof(char)); //malloc for 2 char
    
    // Chance first letter in string
    t[0] = x; t[1] = y;
    
    return t;
}

