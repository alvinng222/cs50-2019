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

bool salt(char a, char b);

int main(void)
{
    char x = 'a', y = '/';

    if (salt(x, y) == 0)
    printf("true\n");
    else printf ("FALSE\n");

}

// function: salt  is  a two-character string chosen from the set [a-zA-Z0-9./]
bool salt(char a, char b)
{
    printf("a : %c  b: %c\n", a, b);
    string salt_type = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./" ;
    for (int i = 0, n = strlen(salt_type); i < n; i++)
    {
        if (a == salt_type[i])
        {
            for (int j = 0, p = strlen(salt_type); j < n; j++)
            {
                //printf("%c\n", salt_type[i]);
                while (b == salt_type[j])
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}
