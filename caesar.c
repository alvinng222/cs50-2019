// CS50x 2019 Problem Set 2 - caesar.c
// 2019 Aug 24
// encrypt messages using Caesar’s cipher

#include <cs50.h> // for string
#include <stdio.h>
#include <string.h> // for strlen

int checkdeci(string cs);
void rotate(string p, int k);

int main(int argc, string argv[])
{
    //check that only second string AND is decimal digit
    if ((argc == 2) && (checkdeci(argv[1]) == 0))
    {
        int key = atoi(argv[1]); //convert 2nd word into integer
        
        //input plaintest, and process 
        string ptext = get_string("plaintext:  ");
        printf("ciphertext: ");
        rotate(ptext, key);
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
    }
}

// function check for NOT decinal
int checkdeci(string cs)
{
    for (int j = 0, n = strlen(cs); j < n; j++)
    {
        char x = cs[j];
        //return if char is NOT decimal from 0 to 9
        if ((x < '0') || (x > '9'))
        {
            return 1;
        }
    }
    //all decimal
    return 0;
}

// function rotate, single char for a to Z will rotate with key
// using c[i] = (p[i] + k) % 26
void rotate(string p, int k)
{
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if (p[i] >= 'A' && p[i] <= 'Z')
        {
            printf("%c", (((p[i] - 65 + k) % 26) + 65));    //65 is 'A' 
        }
        else if (p[i] >= 'a' && p[i] <= 'z')
        {
            printf("%c", (((p[i] - 97 + k) % 26) + 97));    //97 is 'a'
        }
        else
        {
            printf("%c", p[i]);
        }
    }
}
