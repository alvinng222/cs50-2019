// loop1.c
#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
    //char *ap = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcedfghijklmnopqrstuvwxyz";
    char *ap = "ABC";
    int al = strlen(ap); // strlen 52
    // Allocate memory for a keyword of 5 chars
    int keyword_lgth = 5; // was 5
    char *t = malloc((keyword_lgth + 1) * sizeof(char));
    
    for (int k = 2; k <= keyword_lgth; k++)
    {
        int d0=0,d1=0, d2=0, d3=0, d4=0;
        
        // end loop at maximum ways of alpha chars
        int bits = 0;
        int max_bits = al;
        for (int x = 1; x < k; x++)
            max_bits = max_bits*al;
        printf("max_bits: %i\n", max_bits); // ******
        while (bits < max_bits) 
        {
            if (d0 >= al) {d0 = 0; d1++;}  
            if (k > 1 && d1 >= al) {d1 = 0; d2++;}  // for 2+ chars
            if (k > 2 && d2 >= al) {d2 = 0; d3++;}  // for 3+ chars
            if (k > 3 && d3 >= al) {d3 = 0; d4++;}  // for 4+ chars

            if (k == 2){t[0]=ap[d0]; t[1]=ap[d1];}
            if (k == 3){t[0]=ap[d0]; t[1]=ap[d1]; t[2]=ap[d2];}
            if (k == 4){t[0]=ap[d0]; t[1]=ap[d1]; t[2]=ap[d2]; t[3]=ap[d3];}
            if (k == 5){t[0]=ap[d0]; t[1]=ap[d1]; t[2]=ap[d2]; t[3]=ap[d3]; t[4]=ap[d4];}
            //printf for troubleshooting
            if (bits>75 && bits <85) {printf("%s bits:%i\n", t, bits);} bits++;
            d0++;
        }
    } // for int k
    printf("\n");
    free(t); // malloc
}

