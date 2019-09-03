//2. salt  is  a two-character string chosen from the set [a-zA-Z0-9./]
//.1 create constant variable for salt
// salt.c
//abcdefghijklmnopqrstuvwxyz
//ABCDEFGHIJKLMNOPQRSTUVWXYZ
//0123456789./
//abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./
#include <stdio.h>
#include <cs50.h> // string
#include <string.h> // strlen

bool salt(string a);

int main(void)
{
    string z = "*a";
    printf("z: %s | ", z);
    if (salt(z) == 0)
    {
            printf("true\n");
    }
    else
    {
        printf ("FALSE\n");
    }
}

// function: salt  is  a two-character string chosen from the set [a-zA-Z0-9./]
bool salt(string a)
{
    printf(" a : %c  b: %c > ", a[0], a[1]);
    string salt_type = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./" ;
    for (int i = 0, n = strlen(salt_type); i < n; i++)
    {
        if (a[0] == salt_type[i])
        {
            for (int j = 0, p = strlen(salt_type); j < n; j++)
            {
                while (a[1]== salt_type[j])
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}
