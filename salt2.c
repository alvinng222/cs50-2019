//2. salt  is  a two-character string chosen from the set [a-zA-Z0-9./]
//.1 create constant variable for salt
// salt2.c
//abcdefghijklmnopqrstuvwxyz
//ABCDEFGHIJKLMNOPQRSTUVWXYZ
//0123456789./
//abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./
#include <stdio.h>
#include <cs50.h> // string
#include <string.h> // strlen

bool salt(char a);

int main(void)
{
    string z = "A$";
    printf("z: %s | ", z);
    if ( (salt(z[0]) == 0) && (salt(z[1]) == 0) )
    {
            printf("true\n");
    }
    else
    {
        printf ("FALSE\n");
    }
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
/*
 {
    printf(" salt:%c  > ", a);
    string slib = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./" ;
    for (int i = 0, n = strlen(slib); i < n; i++)
    {
        if (a == salt_type[i])
        {
            return 0;
        }
    }
    return 1;
}
 * 
 */
