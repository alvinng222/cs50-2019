//password3.c
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
char *alpha = "ABC";

int main(void)
{
    int algth = strlen(alpha); printf("al : %i\n", algth); //strlen of alpha
    
    // Allocate memory for a keyword of keylgth chars
    int keylgth = 5;
    char *t = malloc((keylgth + 1) * sizeof(char));
    if (!t) { return 1; } // necessary?

    //initiate key words
    t[0] = alpha[0];
    for (int k = 1; k <= keylgth; k++ )
    {
        t[k] = '\0'; // NULL char   
    }
    printf("t :%s\n", t);

    //int bits = 17185;
    //int bits = 65535;
    int bits = 0;
    // permutation of alpha chars to power of no. of chars of keywords 
    int max_bits = algth*algth*algth*algth*algth; 
    while (bits < (max_bits))
    {
    //printf("Total bits: %i \n", bits);
    int c1th = 0; int c2th = 0; int c3th = 0; int c4th;
    
    int c0th = bits; t[0] = alpha[c0th%algth];
    //check if hex1th to be open
    if (c0th >= algth )
    {
        c1th = c0th /algth; t[1] = alpha[c1th%algth];
    }
    //check if hex2th to be open
    if (c1th >= algth )
    {
        c2th = c1th /algth; t[2] = alpha[c2th%algth];
    }
    //check if hex3th to be open
    if (c2th >= algth )
    {
        c3th = c2th /algth; t[3] = alpha[c3th%algth];
    }
    //check if hex3th to be open
    if (c3th >= algth )
    {
        c4th = c3th /algth; t[4] = alpha[c4th%algth];
    }
        
    printf("%s ", t); // print out the malloc string
        
  
    
    //printf("\n");
    
    bits++;
    }
    // Free memory
    free(t);
    
    printf("\n");
    


    /*******
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
    return 0; */

}

