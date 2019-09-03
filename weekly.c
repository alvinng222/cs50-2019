//weekly.c

#include <stdio.h>

int main(void)
{
    int days = 29;
    printf("Total days: %i \n", days);
    int month = days /(4*7);
    int weekth = (days % (4*7)/7);
    int dayth = days % 7;
    printf("month: %i | weekth: %i | days: %i ", month, weekth, dayth);
    
    printf("\n");
}
