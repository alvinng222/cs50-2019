//combi2.c

#include <cs50.h> //string, malloc
#include <stdio.h>


char *combi_2c(char x, char y);
int main(void)
{
    // Get a string
    //string hash = get_string("s: ");
    char *hash = "50cI2vYkF0YU2";

    char x = hash[0], y = hash[1];
    printf("%s \n", combi_2c(x,y));
}


// function to combine 2 char into string//
// need to check for memory leak
char *combi_2c(char x, char y)
{
    // Allocate memory for another string
    //char *t = malloc((2 + 1) * sizeof(char)); //malloc for 2 char
    char t[2] = NULL;
    // Chance first letter in string
    t[0] = x; t[1] = y;
    
    return t;
}
