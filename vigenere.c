// CS50x 2019 Problem Set 2 - vigenere.c
// 2019 Aug 26
// encrypt messages using Vigenere’s cipher
// encrypting messages using a sequence of keys

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int checkalpha(string cs);  //for command in line
char rotate(char p, int k); // rotate single char at keyword
int shift(char c);          // convert to position int

int main(int argc, string argv[])
{
    //check that only second string AND is alpha only
    if ((argc == 2) && (checkalpha(argv[1]) == 0))
    {
        int key, jk;//init for single keyword to integer, rotate position
        int keylgth = strlen(argv[1]); //keyword length
        char p;                        //ciphertext char
        
        //input plaintest
        string ptext = get_string("plaintext:  ");
        printf("ciphertext: ");
        
        //counter for plaintext,i and keyword rotation,j
        for (int i = 0, j = 0, n = strlen(ptext); i < n; i++)
        {
            //j mod key-length, key shift
            jk = j % keylgth;
            key = shift(argv[1][jk]);

            //convert to cipher char, (p + k) % 26
            p = ptext[i];
            if ((p >= 'A' && p <= 'Z') || (p >= 'a' && p <= 'z'))
            {
                printf("%c", rotate(p, key));
                j++;     // next keyword 
            }
            else
            {
                printf("%c", p);
            }
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;     //exit code 1
    }
}

// function check for NOT alphabet
int checkalpha(string cs)
{
    for (int j = 0, n = strlen(cs); j < n; j++)
    {
        char x = cs[j];
        
        //Ret 1 if char is NOT aplha from A to z, or IS between Z to a 
        if ((x < 'A') || (x > 'z') || ((x > 'Z') && (x < 'a'))) 
        {
            return 1;
        }
    }

    return 0;
}

//converting character to its positional integer value
//A or a would be 0, B or b would be 1, Z or z would be 25, etc.
int shift(char c)
{
    int x = 0;
    if ((c >= 'A') && (c <= 'Z'))
    {
        x = ((int) c - 65);
    }
    else if ((c >= 'a') && (c <= 'z'))
    {
        x = ((int) c - 97);
    }
    return x;
}

// function rotate, single char for a to Z will rotate with key, c=(p+k)%26
char rotate(char p, int k)
{
    char c;
    if (p >= 'A' && p <= 'Z')
    {
        c = (((p - 65 + k) % 26) + 65);    //65 is 'A' 
        return c;
    }
    else if (p >= 'a' && p <= 'z')
    {
        c = (((p - 97 + k) % 26) + 97);    //97 is 'a'
        return c;
    }
    else
    {
        return p;
    }
}

/*
$ ./vigenere baz
plaintext:  hello, world!
ciphertext: iekmo, vprke!
*/
