// loop1.c
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <crypt.h>

bool decrypt(char *h, char *sa);
    
int main(void)
{
    //if (decrypt("50cI2vYkF0YU2", "50") == 0)  printf("YES!\n");
    //if (decrypt("51.xJagtPnb6s", "51") == 0)  printf("YES!\n");
    //if (decrypt("50WUNAFdX/yjA", "50") == 0)  printf("YES!\n");
    if (decrypt("50C6B0oz0HWzo", "50") == 0)  printf("YES!\n");
   
}

//function for input of string hash, and salt will printed alpha and return true
bool decrypt(char *h, char *sa)
{
    //char *ap = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcedfghijklmnopqrstuvwxyz";
    //char *ap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *ap = "ABC";
    int al = strlen(ap); // strlen 52
    // Allocate memory for a keyword of 5 chars
    int keyword_lgth = 5; // was 5
    char *t = malloc((keyword_lgth + 1) * sizeof(char));
    
    for (int k = 2; k <= keyword_lgth; k++)
    {
        //int k = keyword_lgth; //int keylgth <= keyword_lgth;
        int d0=0,d1=0, d2=0, d3=0, d4=0;
        //int k = 5; // keyword lgth
         //printf("tk: %s | keylgth:%i | keyword_lgth:%i || ", t, keylgth, keyword_lgth);
        int bits = 0;
        // maximum ways of alpha chars. power of no. of chars of keywords 
        int max_bits = al;
        for (int x = 1; x < k; x++)
            max_bits = max_bits*al;
        printf("max_bits: %i\n", max_bits);
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
            
            char *thash = crypt(t, sa); // crypt 
            if  (strcmp(thash, h) == 0) // compare with input
            {
                printf("%s \n", t); // print out the malloc string
                free(t);
                return 0;
            }
            
            //printf troubleshoot
            if (bits%140608 <= 0) printf("%i ", max_bits-bits) ;  // ****
            //if (bits>75 && bits <85) {printf("%s bits:%i\n", t, bits);} 
            bits++;
            d0++;
            //if (bits > max_bits) {printf("return??"); return 1;}
        }
    } // for int k
    printf("\n");
    free(t);
    return 1;
}
