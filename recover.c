/*****
# recover.c
*****/
// cs50-2019 Problem set 3 - recover.c
// Sep 11, 2019

// digital cameras often initialize cards with a FAT file
//   system whose "block size" is 512 bytes (B).
// JPEG the first three bytes of JPEGs are 0xff 0xd8 0xff,
//   fourth byte, meanwhile, is either 0xe0 .. 0xef
// A photo that’s 1 MB (1,048,576 B) takes ÷ 512 = 2048 "blocks"

/* Pseudocode
 * open 0th image file 000.jpg
 * #A  do loop from
 * Read infile
 * Check Header, jpegHdr
 * if yes header
 *   closed and open new file
 *   next filename  ++
 * Just write (over) data to outptr
 * loop to #A. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>        // for bool

bool jpegHdr(int byte4);    // check 4 bytes header of JPEG

//int main(void)
int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: recover infile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // allocate memory for handle 512 (4*128) bytes data,
    int buffer[128];        //int *buffer = malloc((128) * sizeof(int));

    // create and open image file by sprint
    // int sprintf(char *str, const char *format, ...);
    int fn = 0;                         // filename from running number
    char *outfile = malloc((7 + 1) * sizeof(char)); // strlen is 7
    sprintf(outfile, "%03i.jpg", fn);   // pre-create, will be overwrite

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 3;
    }

    buffer[0] = 0x0;
    do
    {
        if ((jpegHdr(buffer[0]) == 0))
        {
            fclose(outptr);                     // close outfile

            sprintf(outfile, "%03i.jpg", fn);   //create next jpg name
            outptr = fopen(outfile, "w");       // open new output file
            fn++;                               // next filename
        }

        // just continue to write, regardless of front non-image data
        // if (buffer[0] != 0)  // skip buffer if 0x0 - don't work!
        {
            fwrite(buffer, 128, 1, outptr);
        }
        
        fread(buffer, 128, 1, inptr); // read the first block of file
    }
    while (feof(inptr) != 1);

    fclose(outptr);     // close outfile
    fclose(inptr);      // close infile
    free(outfile);      // Free memory
    return 0;           // success
}

// check if first three bytes: 0xff 0xd8 0xff,
// + fourth byte, is either 0xe0, 0xe1, 0xe2, ... 0xed, 0xee, or 0xef.
bool jpegHdr(int byte4)
{
    int Hdr = 0xe0ffd8ff;
    do
    {
        if (byte4 == Hdr)
        {
            return 0;       // return if header match
        }

        Hdr = Hdr + 0x01000000;
    }
    while (Hdr < 0xf0000000);

    return 1;
}

/* $ rm -f *.jpg
$ valgrind ./recover card.raw --leak-check=full
$ echo $?
0
~/work3/ $ style50 recover.c
~/work3/ $ check50 cs50/problems/2019/x/recover
$ submit50 cs50/problems/2019/x/recover */
