//cs50-2019 pset3 resize.c
// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

// int main(void)
int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // remember filenames
    double f = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // f is integer, or else return with 1
    // if y negative integer than f = 0
    if (f <= 0)
    {
        printf("The resize factor, must satisfy 0 < n <= 100.\n");
        // n, the resize factor, must be a float

        return 1; // kill the program *****
    }
    //printf("f= %0.2f  ok good!\n", f);
    //return 0; // kill the program *****

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // my struct for infile RGB only
    int xH = abs(bi.biHeight); int xW = bi.biWidth;
    RGBTRIPLE xRGB[xH][xW];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // copy to struc
            xRGB[i][j] = triple;

            // write RGB triple to outfile
            // fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    ///  was
        }


        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        /*/ then add it back (to demonstrate how)      was
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        } */
    }


    // PROCESS
    int nH = xH*f; //printf("nH; %i\n", nH);
    int nW = xW*f; //printf("nW; %i\n", nW);

    RGBTRIPLE NewRGB[nH][nW];
    for (int na = 0; na < nH; na++)
    {
        for (int nb = 0; nb < nW; nb++)
        {
            int fna = na/f + 1/f/2; int fnb = nb/f + 1/f/2; //+ 1/f/2 is start from half way
            NewRGB[na][nb] = xRGB[fna][fnb];
        }
    }

    // new file header and info header
    BITMAPFILEHEADER nf; nf = bf;
    BITMAPINFOHEADER ni; ni = bi;
    ni.biWidth = f * bi.biWidth; // nW
    ni.biHeight = f * bi.biHeight; // nH
    int nipadding = (4 - (ni.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int scanline =  (sizeof(RGBTRIPLE) * ni.biWidth) + nipadding;  // size of scanline
    ni.biSizeImage = scanline * abs(ni.biHeight);
    nf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + ni.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&nf, sizeof(BITMAPFILEHEADER), 1, outptr);  // was
    //printf("write: nf, sizeof BITMAPFILEHEADER: %lu | ", sizeof(BITMAPFILEHEADER) ); /// no change ****
    // write outfile's BITMAPINFOHEADER
    fwrite(&ni, sizeof(BITMAPINFOHEADER), 1, outptr);   // was
    //printf("write: nf, sizeof BITMAPINFOHEADER: %lu\n", sizeof(BITMAPINFOHEADER) );  /// no change ****

    //printf("new width: %d | new height: %d | new biSizeImage: %d | new bfSize: %d \n",
    //   ni.biWidth, ni.biHeight, ni.biSizeImage, nf.bfSize); // ****

    ///// PRIINT //////
    //int m = nibiWidth;
    for (int i=0; i<nH; i++)
    {
        for (int j=0; j<nW; j++)
        {
            //printf("%x%x%x ", NewRGB[i][j].rgbtBlue, NewRGB[i][j].rgbtGreen, NewRGB[i][j].rgbtRed);
            // write RGB triple to outfile
            fwrite(&NewRGB[i][j], sizeof(RGBTRIPLE), 1, outptr);    ///  was
        }

        // then add it back (to demonstrate how)      was
        for (int k = 0; k < nipadding; k++)
        {
           fputc(0x00, outptr);
           //printf("p");
        }


        //printf("\n");
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    //printf("\n");   // ****

    // success
    return 0;
}

/*
large.bmp
write: nf, sizeof BITMAPFILEHEADER: 14 | write: nf, sizeof BITMAPINFOHEADER: 40
old width: 12 | old height: -12 | old biSizeImage: 432 | old bfSize: 486
factor :  1.00

small.bmp
old width: 3 | old height: -3 | old biSizeImage: 36 | old bfSize: 90
*/