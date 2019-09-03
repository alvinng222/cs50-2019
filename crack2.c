// CS50x 2019 Problem Set 1 - crack.c
// 2019 Aug 30
//$ ./crack 50cI2vYkF0YU2
//LOL

#include <cs50.h> //string, malloc, bool
#include <stdio.h>
#include <string.h> // strlen
#include <crypt.h>

char *combi_2c(char x, char y);
bool salt(char a);
bool decrypt(char *h, char *sa);

int main(int argc, char *argv[])
{
    if ((argc == 2) && ( strlen(argv[1]) == 13 ))
    {
        printf("ok salt is ");
        char *s = combi_2c(argv[1][0], argv[1][1]);
        printf("%s, and is ", s);
        if ( (salt(s[0]) == 0) && (salt(s[1]) == 0) ) /// issues on SALT !!
        {
            printf("true\n");
            
            if (decrypt(argv[1], s) == 0)
            {
                printf("yes\n");
                return 0;
            }
            else 
            {
                printf("NO\n");
                return 1;
            }
        }
        else
        {
            printf ("FALSE\n");
        }
        
    }
    else
    {
        printf("Usage: ./crack hash\n");
    }
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

// function: salt  is  a two-character string chosen from the set [a-zA-Z0-9./]
bool salt(char a)
{
    printf(" salt:%c  > ", a);
    char *slib1 = "abcdefghijklmnopqrstuvwxyz";
    char *slib2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *slib3 = "0123456789./";
    for (int i = 0, n = strlen(slib1); i < n; i++)
    { if (a == slib1[i]) return 0;}
    for (int i = 0, n = strlen(slib2); i < n; i++)
    { if (a == slib2[i]) return 0;}
    for (int i = 0, n = strlen(slib3); i < n; i++)
    { if (a == slib3[i]) return 0;}
    return 1;
}

//function for input of string hash, and salt will printed alpha and return true
bool decrypt(char *h, char *sa)
{
    //char *ap = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcedfghijklmnopqrstuvwxyz";
    //char *alpha = "KLOP";
    char *ap = "ABC";
    int al = strlen(ap); // strlen 52
    //printf("al : %i\n", algth); //strlen of alpha
    
    // Allocate memory for a keyword of 5 chars
    int keyword_lgth = 5; // was 5
    char *t = malloc((keyword_lgth + 1) * sizeof(char));
    
    for (int keylgth = 2; keylgth <= keyword_lgth; keylgth++)
    {
        //printf("pre-tk:%s | keylgth:%i | keyword_lgth:%i ||", t, keylgth, keyword_lgth);
        //initiate key words to 'AAAAA\0"
        for (int k = 0; k < keylgth; k++ )
            t[k] = ap[0];   
        t[keylgth] = '\0'; // NULL char  
        
        //printf("tk: %s | keylgth:%i | keyword_lgth:%i || ", t, keylgth, keyword_lgth);
        int bits = 0;
        // maximum ways of alpha chars. power of no. of chars of keywords 
        int max_bits = al;
        for (int x = 1; x < keylgth; x++)
            max_bits = max_bits*al;
        
        printf(" keylgth: %i | max_bits: %i | t : %s | ",keylgth, max_bits, t); //*******
        // using bits to divide to individual position of chars
        int c0, c1, c2, c3, c4;
        while (bits < max_bits)
        {
            c0 = bits;
                                         t[0] = ap[c0 % al];
            if (c0 >= al) {c1 = c0 / al; t[1] = ap[c1 % al];}
            if (c1 >= al) {c2 = c1 / al; t[2] = ap[c2 % al];}
            if (c2 >= al) {c3 = c2 / al; t[3] = ap[c3 % al];}
            if (c3 >= al) {c4 = c3 / al; t[4] = ap[c4 % al];}
            
            if ((bits >= 0) && (bits < 1)) printf("bits:%i t:%s c1:%i c2:%i c3:%i c4:%i al:%i\n",bits,t,c1,c2,c3,c4,al);
            char *thash = crypt(t, sa); // crypt 

            if  (strcmp(thash, h) == 0) // compare with input
            {
                printf("%s \n", t); // print out the malloc string
                free(t);
                return 0;
            }
            bits++; //while bits < max_bits
            if (bits%140608 <= 0) printf("%i ", max_bits-bits) ;  // ****
        }
    }
    // Free memory
    free(t);
    return 1;
}

/*
 *  ./crypt ABCD 61
key: ABCD | salt: 61 | crypt: 61xZCsOEZEGCc
 ./crypt Hello hi
key: Hello | salt: hi | crypt: hisc/cgqERS3o
$ ./crypt AAAAA hi
key: AAAAA | salt: hi | crypt: hiYr2cskji5PQ

key: zzzz | salt: 99 | crypt: 99lznoGfhbfkk 
key: AAAAA | salt: 55 | crypt: 55SEuX4NARDrM : NO
key: AABAA | salt: 55 | crypt: 55rUxg7prnO56 : No
key: BBBAA | salt: 55 | crypt: 55DgsqkW.KFog : No

key: BBBBB | salt: 55 | crypt: 55y.7YhrIihIk : Yes
key: BBBBA | salt: 55 | crypt: 554PQi5n3EJ3U : Yes
key: ABBBB | salt: 55 | crypt: 55Urzjh5KZ6/o : Yes
key: AABBB | salt: 55 | crypt: 55UzqnAst9xgQ : Yes
key: BBBAB | salt: 55 | crypt: 555rYhkhnXbIg : Yes



 * */
