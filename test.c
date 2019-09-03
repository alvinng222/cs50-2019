#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char *test(char x, char y);
string combi_2c(char x, char y);
int main(void)
{
    
    char x = 'A', y = 'z';

    char *s = test(x,y);
    printf("s: %s | \n", s); 
    
    /*/ Get a string
    //string s = get_string("s: ");
    string hash = "50cI2vYkF0YU2";

    char x = hash[0], y = hash[1];
    printf("%s \n", combi_2c(x,y)); */
}

char *test(char x, char y)
{
    char z[3];
    z[0] = x; 
    z[1] = y;
    z[2] = '\0';
    printf(""); // ???
    char *v = z;
    return v;
}


// function to combine 2 char into string//
// need to check for memory leak
string combi_2c(char x, char y)
{
    // Allocate memory for another string
    char *t = malloc((2 + 1) * sizeof(char)); //malloc for 2 char
    //if (!t)
    //{
    //    return 1;
    //}
    
    // Chance first letter in string
    t[0] = x; t[1] = y;

    // Print string 
    printf("t: %s\n", t);
    
    // Free memory
    //free(t);
    return t;
}
/*
#include <stdio.h>

int main(void)
{
    char s[1];
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
}
*/
//$ ./test
//s: 01234567
