# Questions

## What's `stdint.h`?

Header for common data types, or aliases for C/C++ primitive data types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

'uint8_t' is an 8-bit unsigned, such as BYTE
'uint32_t' is a 32-bit unsigned integer, such as DWORD;
'int32_t' is a 32-bit signed integer, such as LONG;
'unit16_t' is a 16-bit unsigned integer, such as WORD.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

'BYTE' is 1 byte;
'DWORD' is 4 bytes;
'LONG' is 4 bytes;
'WORD' is 2 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x4d42 WORD bfType of BITMAPFILEHEADER 

## What's the difference between `bfSize` and `biSize`?

bfSize: The size, in bytes, of the bitmap file.
biSize: The number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

biHeight
The height of the bitmap, in pixels. If biHeight is positive, the bitmap is a bottom-up DIB and its origin is the lower-left corner. If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.


## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount: The number of bits-per-pixel. The biBitCount member of the BITMAPINFOHEADER structure determines the number of bits that define each pixel and the maximum number of colors in the bitmap. 

## Why might `fopen` return `NULL` in `copy.c`?

Could not write or crate another file.

## Why is the third argument to `fread` always `1` in our code?

to read ONE time

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

TODO

## What is `SEEK_CUR`?

TODO
