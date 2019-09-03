// CS50x 2019 Problem Set 1 - crack.c
// 2019 Aug 30
// program to crack the given password
// each password has been hashed with C’s DES-based (not MD5-based) crypt function.

#include <cs50.h> // string, malloc, bool
#include <stdio.h>
#include <string.h> // strlen
#include <crypt.h>

char *combi_2c(char x, char y); // function to combine 2 char into string
bool salt(char a); // check salt, a two-character string 
bool decrypt(char *h, char *sa); //input of string hash, salt, if true will print out keyword.

int main(int argc, char *argv[])
{
    if ((argc == 2) && (strlen(argv[1]) == 13))
    {
        // quatify the 2 chars salt from hash
        char *s = combi_2c(argv[1][0], argv[1][1]);
        if ((salt(s[0]) == 0) && (salt(s[1]) == 0))
        {
            if (decrypt(argv[1], s) == 0)
            {
                return 0; // printf("yes\n");
            }
            else 
            {
                return 1; // printf("NO\n");
            }
        }
    }
    else
    {
        printf("Usage: ./crack hash\n");
    }
}

// function to combine 2 char into string
// need to check for memory leak
char *combi_2c(char x, char y)
{
    // Allocate memory for another string
    char *t = malloc((2 + 1) * sizeof(char)); // malloc for 2 char
    // Chance first letter in string
    t[0] = x; 
    t[1] = y;
    return t;
}

// function: salt is  a two-character string chosen from the set [a-zA-Z0-9./]
bool salt(char a)
{
    printf(""); // got issue if without this
    char *slib1 = "abcdefghijklmnopqrstuvwxyz";
    char *slib2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *slib3 = "0123456789./";
    for (int i = 0, n = strlen(slib1); i < n; i++)
    { 
        if (a == slib1[i]) 
        {
            return 0;
        }
    }
    for (int i = 0, n = strlen(slib2); i < n; i++)
    { 
        if (a == slib2[i]) 
        {
            return 0;
        }
    }
    for (int i = 0, n = strlen(slib3); i < n; i++)
    {
        if (a == slib3[i]) 
        {
            return 0;
        }
    }
    return 1;
}

// function for input of hash,h and salt, sa will printed alpha and return true
// to convert into hash from all alpha on chars of keyword, and compare against input, h. 
bool decrypt(char *h, char *sa)
{
    char *ap = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcedfghijklmnopqrstuvwxyz";

    int al = strlen(ap); // strlen 52
    // Allocate memory for a keyword of 5 chars
    int keyword_lgth = 5; // specfication of keyword is 5 chars
    char *t = malloc((keyword_lgth + 1) * sizeof(char));
    
    for (int k = 2; k <= keyword_lgth; k++)
    {
        int d0 = 0, d1 = 0, d2 = 0, d3 = 0, d4 = 0;
        // set counters for maximum loops
        int bits = 0;
        // maximum ways of alpha chars, power of no. of chars of keywords 
        int max_bits = al;
        for (int x = 1; x < k; x++)
        {
            max_bits = max_bits * al;
        }
        //printf("max_bits: %i\n", max_bits);  
        int test = 0, test1 = 0; // for trouble shooting
        
        // while loop for increment for individual chars of keyword
        while (bits < max_bits) 
        {
            if (d0 >= al) 
            {
                d0 = 0; 
                d1++;
            }  
            if (k > 1 && d1 >= al) 
            {
                d1 = 0; 
                d2++;    // for 2+ chars
            } 
            if (k > 2 && d2 >= al) 
            {
                d2 = 0; 
                d3++;    // for 3+ chars
            }  
            if (k > 3 && d3 >= al) 
            {
                d3 = 0; 
                d4++;     // for 4+ chars
            } 

            if (k == 2)
            {
                t[0] = ap[d0]; 
                t[1] = ap[d1];
            }
            if (k == 3)
            {
                t[0] = ap[d0]; 
                t[1] = ap[d1]; 
                t[2] = ap[d2];
            }
            if (k == 4)
            {
                t[0] = ap[d0]; 
                t[1] = ap[d1]; 
                t[2] = ap[d2]; 
                t[3] = ap[d3];
            }
            if (k == 5)
            {
                t[0] = ap[d0]; 
                t[1] = ap[d1]; 
                t[2] = ap[d2]; 
                t[3] = ap[d3]; 
                t[4] = ap[d4];
            }
            
            // compare the crypt result against input
            char *thash = crypt(t, sa); 
            if (strcmp(thash, h) == 0) 
            {
                printf("%s \n", t); // print out the malloc string
                free(t);
                return 0;
            }
            
            //// printf troubleshoot
            //if (test != d4) {printf(" %c %i\n", ap[d4], max_bits - bits); test = d4;}
            //if (test1 != d3) {printf("."); test1 = d3;}

            bits++; // for while loop
            d0++;   // next increment of char 0th
        }
    } // for int k
    printf("\n");
    free(t);
    return 1;
}

/*
  /etc/shadow might look like: brian:51.xJagtPnb6s, bjbrown:50GApilQSG3E2
below is sample hash input and resulting keyword
$ ./crack 50cI2vYkF0YU2 > LOL
$ ./crack 51.xJagtPnb6s > TF 
$ ./crack 50GApilQSG3E2 > 5 chars > Upenn
$ ./crack 502sDZxA/ybHs > 5 chars > puppy
$ ./crack 50C6B0oz0HWzo > FTW
$ ./crack 50WUNAFdX/yjA > Yale
$ ./crack 50n0AAUD.pL8g > 5 chars
$ ./crack 50CcfIk1QrPr6 > 5 chars
$ ./crack 50JIIyhDORqMU > nope
$ ./crack 51v3Nh6ZWGHOQ > ROFL
$ ./crack 61v1CDwwP95bY > hola
$ ./crack 508ny6Rw0aRio > sean
$ ./crack 50cI2vYkF0YU2 > LOL

$ check50 cs50/problems/2019/x/crack
:) crack submitted
style50 crack.c
*/
