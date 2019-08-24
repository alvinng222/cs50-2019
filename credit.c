// CS50x 2019 Problem Set 1 - credit.c
// 2019 Aug 22
// using Luhn's Algorithn to to check Amex, Visa or Master is valid

#include <stdio.h>
#include <cs50.h> // for get_long
    
long digit13 = 1000000000000; //visa 13 digits number
long digit16 = 1000000000000000; //visa or Master 16 digits number 
long digit15 = 100000000000000; //Amx 15 digits number 

int luhn(long y);
int parity(int counter);

int main(void)
{
    //prompt for number between 13 to 17 digits
    long number;
    int lastdigit;
    do
    {
        number = get_long("Number: ");
    }
    while (number < digit13 || number > digit16 * 10);
    
    //if function Luhn valid, check type
    if (luhn(number)==0)
    {
        //Visa uses 13-digit numbers, start with 4. Or
        if (number > digit13 && number < digit13 * 10) 
        {
            lastdigit = (number / digit13);
            if (lastdigit == 4)
            {
                printf("VISA\n");      
            }
            else
            {
            printf("INVALID\n");
            }
        }
        //Visa uses 16-digit numbers, start with 4;
        //Master uses 16-digit numbers, start with 51,52,53,54, or 55. 
        else if (number > digit16 && number < digit16 * 10) 
        {
            lastdigit = (number / (digit16 / 10));
            if ((lastdigit / 10) == 4)
            {
                printf("VISA\n");      
            }
            else if ((lastdigit > 50) && (lastdigit < 56))
            {
                printf("MASTER\n");      
            }
            else
            {
            printf("INVALID\n");
            }
        }
        //Amex uses 15-digit numbers, start with 34 or 37
        else if (number > digit15 && number < digit15 * 10) 
        {
            lastdigit = (number / (digit15 / 10));
            if (lastdigit == 37 || lastdigit == 34)
            {
                printf("AMERICAN EXPRESS\n");      
            }
            else
            {
            printf("INVALID\n");
            }
        }
        else
        {
        printf("INVALID\n");
        } 
    }
    else
    {
    printf("INVALID\n");
    }
}

//Luhn algorithm, input long number, return with 0 for valid
int luhn(long y)
{
    //loop and get the remainder by divide by 10, till variable become 0
    long Num = y;
    int digit1, digit2, counter = 0, checksum = 0;

    do
    {
        counter ++; // start with counter = 1
        
        //get the first digit by modular 10
        digit1 = Num % 10;

        //perform a check for Odd digit or Even digit
        if (parity(counter) == 1)
        {
            //if counter is odd, add the 1st digit to checksum
            checksum += digit1;
        }
        else
        {
            //if counter is even, double the digit
            //if more than 9, split digit and add into checksum
            digit2 = digit1 * 2;
            if (digit2 > 9)
            {
                checksum += (digit2 % 10); // add 1st digit
                checksum += (digit2 / 10); // and 2nd digit
            }
            else
            {
            checksum += digit2;         
            }
        }
        Num = Num / 10;  // next digit
    }
    while (Num > 0);

    //checksum modulus 10
    return checksum % 10;
}

// function for party on Odd or Even 
int parity(int counter)
{
    // Check parity of integer
    if (counter % 2 == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
