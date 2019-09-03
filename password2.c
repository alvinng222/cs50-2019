//password2.c
/*
Assume that each password is no longer than five (5) characters. Gasp!
Assume that each password is composed entirely of alphabetical characters (uppercase and/or lowercase).
*/
// loop around all alphabet from A till ZZZZZ, till match with crypt hash

#include <crypt.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h> //strlen

char *hash = "50cI2vYkF0YU2";
char *salt = "50";
char *alpha = "ABCDEFGHIJKLP";

int main(void)
{
    for (int n = 1; n <= 5; n++) // from 1 to 5 chars
    {
        printf("strlen: %i\n", n);
        // Allocate memory for another string
        char *t = malloc((n + 1) * sizeof(char));
        if (!t) { return 1; } // necessary?

        // Copy alpha into memory
        // runing i pos in till n pos
        for (int i = 0; i <= n; i++) //eg if n = 2, will be 2 columns
        {
            t[i] = alpha[0];
            t[n] = '\0'; // NULL char
        }

        printf("t: %s\n", t);

        // Free memory
        free(t);
    }        
    return 0;

}


