//test5.c
#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

bool decrypt(char *h, char *sa);

int main(void)
{
    char *s = "50";
    char *hash = "50cI2vYkF0YU2"; 
    if (decrypt(hash, s) == 0)
    {
        printf("yes\n");
    }
}

//function for input of string hash, and salt will printed alpha and return true
bool decrypt(char *h, char *sa)
{
    //char *alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcedfghijklmnopqrstuvwxyz";
    char *alpha = "KLOP";
    //char *alpha = "ABC";
    int algth = strlen(alpha);
    //printf("al : %i\n", algth); //strlen of alpha
    
    // Allocate memory for a keyword of 5 chars
    int keyword_lgth = 5; // was 5
    char *t = malloc((keyword_lgth + 1) * sizeof(char));
    
    for (int keylgth = 2; keylgth <= keyword_lgth; keylgth++)
    {
        //initiate key words to 'AAAAA\0"
        for (int k = 0; k < keylgth; k++ )
        {
            t[k] = alpha[0];   
        }
        printf("tk: %s ", t);
        int bits = 0;
        // maximum ways of alpha chars. power of no. of chars of keywords 
        int max_bits = algth;
        for (int x = 1; x < keylgth; x++)
        {
            max_bits = max_bits*algth;
        }
        printf("\n keylgth: %i | max_bits: %i\n",keylgth, max_bits);
        // using bits to divide to individual position of chars
        int c0th, c1th, c2th, c3th, c4th;
        while (bits < max_bits)
        {
            //int c1th = 0; int c2th = 0; int c3th = 0; int c4th = 0;
            c0th = bits; t[0] = alpha[c0th%algth];
            //check if hex1th to be open
            if (c0th >= algth )
            {
                c1th = c0th /algth; t[1] = alpha[c1th%algth];
            }
            //check if hex2th to be open
            if (c1th >= algth)
            {
                c2th = c1th /algth; t[2] = alpha[c2th%algth];
            }
            // check if hex3th to be open  *****
            if (c2th >= algth )
            {
                c3th = c2th /algth; t[3] = alpha[c3th%algth];
            }
            //check if hex3th to be open
            if (c3th >= algth )
            {
                c4th = c3th /algth; t[4] = alpha[c4th%algth];
            }
            
            //printf(".");
            char *thash = crypt(t, sa); 
            //printf("%s: %s ",t, thash);
            //printf("%s ", t);

            if  (strcmp(thash, h) == 0) // compare with input
            {
                printf("%s \n", t); // print out the malloc string
                free(t);
                return 0;
            }
            bits++; //while bits < max_bits
        }
    }
    // Free memory
    free(t);
    return 1;
}

/*
int main(void)
{
    int a = 3; 
    int bits = 0;
    int max_bits = 10;//a*a*a; 
    while (bits < (max_bits))
    {
        int c1th = 0; int c2th = 0;

        int c0th = bits; printf("%i ", c0th % a);
        //check if hex1th to be open
        if (c0th >= a )
        {
            c1th = c0th /a; printf("%i ",c1th % a);
        }
        //check if hex2th to be open
        if (c1th >= a )
        {
            c2th = c1th /a; printf("%i ",c2th % a);
        }

        printf("c0th: %i | c1th: %i | c2th : %i\n", c0th, c1th, c2th);
        bits++;
    }
}
*/
