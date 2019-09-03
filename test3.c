// test for null char at malloc
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Get a string
    char *alpha = "ABCDE";
    char *s = "ABCD";
    if (!s)
    {
        return 1;
    }
    //int n = strlen(s);
    //
    int n = 2; // let say n = 2

    printf("strlen: %i\n", n);
    // Allocate memory for another string
    char *t = malloc((n + 1) * sizeof(char));
    if (!t) { return 1; }

    // print matrix string into memory
    for (int i = 0; i <= n; i++)
    {
        t[i] = alpha[0];
        t[n] = '\0'; // NULL char
    }

    printf("t: %s\n", t);

    // Free memory
    free(t);
   
    return 0;
 
}

/*
 AA BA CA ... 
 AB BB CB ...
 AC BC CC ...
 */
