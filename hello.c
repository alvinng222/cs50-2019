// hello.c 20190822
// Problem Set 1
// Says hello to the world

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string ("What is your name?\n");
    printf("hello, %s\n", name);
}
