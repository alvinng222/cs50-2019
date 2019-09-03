// CS50x 2019 Problem Set 1 - crack.c
// 2019 Aug 30
//$ ./crack 50cI2vYkF0YU2 > LOL
//$ ./crack 51.xJagtPnb6s > TF 
//$ ./crack 50GApilQSG3E2 > 5 chars
//$ ./crack 502sDZxA/ybHs > 5 chars
//./crack 50C6B0oz0HWzo > FTW
//./crack 50WUNAFdX/yjA > Yale
//./crack 50n0AAUD.pL8g> 5 chars
// ./crack 50CcfIk1QrPr6 > 5 chars
// ./crack 50JIIyhDORqMU > nope
// ./crack 51v3Nh6ZWGHOQ > ROFL
// ./crack 61v1CDwwP95bY > hola
// ./crack 508ny6Rw0aRio > sean
// ./crack 50cI2vYkF0YU2 > LOL


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
        //printf("ok salt is ");
        char *s = combi_2c(argv[1][0], argv[1][1]);
        //printf("%s, and is ", s);
        if ( (salt(s[0]) == 0) && (salt(s[1]) == 0) ) /// issues on SALT !!
        {
            //printf("true\n");
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
    printf(""); // got issue if without this
    char *slib1 = "abcdefghijklmnopqrstuvwxyz";
    char *slib2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *slib3 = "0123456789./";
    for (int i = 0, n = strlen(slib1); i < n; i++)
    { 
        if (a == slib1[i]) 
            return 0;
    }
    for (int i = 0, n = strlen(slib2); i < n; i++)
    { 
        if (a == slib2[i]) 
            return 0;
    }
    for (int i = 0, n = strlen(slib3); i < n; i++)
    {
        if (a == slib3[i]) 
            return 0;
    }
    return 1;
}

//function for input of string hash, and salt will printed alpha and return true
bool decrypt(char *h, char *sa)
{
    char *ap = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcedfghijklmnopqrstuvwxyz";
    //char *ap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //char *ap = "ABC";
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
        int test = 0, test1 = 0; // for trouble shooting
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
            //if (test != d4) {printf("%i ", max_bits-bits); test = d4;}  // ****
            if (test != d4) {printf(" %c %i\n", ap[d4], max_bits-bits); test = d4;}  // ****
            if (test1 != d3) {printf("."); test1 = d3;}  // ****
            //if (bits%140608 <= 0) printf("%i ", max_bits-bits) ;  // ****
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


/*
 *  ./crypt ABCD 61
key: ABCD | salt: 61 | crypt: 61xZCsOEZEGCc : YES
 ./crypt Hello hi
key: Hello | salt: hi | crypt: hisc/cgqERS3o > too long
$ ./crypt AAAAA hi
key: AAAAA | salt: hi | crypt: hiYr2cskji5PQ : YES
 ./crypt zzzz 99
key: zzzz | salt: 99 | crypt: 99lznoGfhbfkk : YES
key: AAAAA | salt: 55 | crypt: 55SEuX4NARDrM : YES
key: AABAA | salt: 55 | crypt: 55rUxg7prnO56 : YES
key: BBBAA | salt: 55 | crypt: 55DgsqkW.KFog : YES

key: BBBBB | salt: 55 | crypt: 55y.7YhrIihIk : Yes
key: BBBBA | salt: 55 | crypt: 554PQi5n3EJ3U : Yes
key: ABBBB | salt: 55 | crypt: 55Urzjh5KZ6/o : Yes
key: AABBB | salt: 55 | crypt: 55UzqnAst9xgQ : Yes
key: BBBAB | salt: 55 | crypt: 555rYhkhnXbIg : Yes

 */
