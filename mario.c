// CS50x 2019 Problem Set 1 - mario.c (more)
// 2019 Aug 22

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //prompt for height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //printing #
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (j < (height - i - 1))
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("  ");
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
