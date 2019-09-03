#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    int c0, c1, c2, c3, c4;
    int al = 3; char *ap = "ABC";
    
    // Allocate memory for a keyword of 5 chars
    int keyword_lgth = 3; // was 5
    char *t = malloc((keyword_lgth + 1) * sizeof(char));
    
    for (int keylgth = 2; keylgth <= keyword_lgth; keylgth++) // ****** issues here??
    {
        for (int k = 0; k < keylgth; k++ ) t[k] = ap[0];   
            t[keylgth] = '\0'; // NULL char  
            printf("t at k: %s\n",t);

        int bits = 0; 
        while (bits < 9)
        {
                c0 = bits;               t[0] = ap[c0 % al];
            if (c0 >= al) {c1 = c0 / al; t[1] = ap[c1 % al];}
            if ((keylgth > 2) && (c1 >= al)) {c2 = c1 / al; t[2] = ap[c2 % al];}
            //if ((keylgth > 3) && (c2 >= al)) {c3 = c2 / al; t[3] = ap[c3 % al];}
            //if ((keylgth > 4) && (c3 >= al)) {c4 = c3 / al; t[4] = ap[c4 % al];}
            bits++;
            printf("t:%s bits: %i\n",t, bits);
        }
        free(t);
        printf("\n");
    }
}
