//hex.c

#include <stdio.h>
char *alpha = "0123456789ABCDEF";

int main(void)
{
    //int bits = 16;
    //int bits = 4095;
    //int bits = 65535;
    int bits = 0;
    while (bits < 64)
    {
    
    //printf("Total bits: %i \n", bits);
    int hex1th = 0; int hex2th = 0; int hex3th = 0;
    
    int hex0th = bits;
    //check if hex1th to be open
    if (hex0th >= 16 )
    {
        hex1th = hex0th /16;
    }
    //check if hex2th to be open
    if (hex1th >= 16 )
    {
        hex2th = hex1th /16;
    }
    //check if hex3th to be open
    if (hex2th >= 16 )
    {
        hex3th = hex2th /16;
    }
    //printf("hex3th: %i | hex2th: %i | hex1th: %i | hex0th: %i \n",hex3th, hex2th, hex1th, hex0th);
    //printf("hex deci: %i %i %i %i",hex3th%16, hex2th%16, hex1th%16, hex0th%16);
    printf("HexDeci: %c%c%c%c ", alpha[hex3th%16],alpha[hex2th%16],alpha[hex1th%16],alpha[hex0th%16] );
    printf("\n");
    bits++;
    }
    printf("(15*16*16)+(15*16)+15= %i\n",(15*16*16)+(15*16)+15 );
    printf("(15*16*16*16)+(15*16*16)+(15*16)+15= %i\n", 
           (15*16*16*16)+(15*16*16)+(15*16)+15 );
}

