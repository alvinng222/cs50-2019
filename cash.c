// CS50x 2019 Problem Set 1 - cash.c (less)
// 2019 Aug 23

#include <cs50.h>
#include <stdio.h>
#include <math.h>

float dollars;
int cents;
int cashbal;

int main(void)
{
    // Prompt user for input, and convert to cents
    do
    {
        dollars = get_float("Change: ");
        cents = round(dollars * 100);
    }
    while (cents < 1);
    
    cashbal = cents;
    
    //quarter, 25 cents  
    int qtr_count = (cashbal / 25);
    cashbal = (cashbal - (qtr_count * 25));

    // dimes 10 cents
    int dim_count = (cashbal / 10);
    cashbal = (cashbal - (dim_count * 10));

    // nickels, 5 cents
    int nic_count = (cashbal / 5);
    cashbal = (cashbal - (nic_count * 5));

    //pennies, 1 cent
    int pen_count = (cashbal / 1);
    cashbal = (cashbal - (pen_count * 1));
    
    //total cash change
    //printf("Quarter:%i; Dimes:%i, Nickel:%i, Penny:%i\n", qtr_count,dim_count,nic_count,pen_count);
    printf("%i\n", (qtr_count + dim_count + nic_count + pen_count));
}
