# Image_effects
Adds special effects to PGM and PPM images.

Referece @http://netpbm.sourceforge.net/doc/pgm.html

PGM: portable gray map, images are grayscale file in either binary or ascii format.
PPM: Netpbm color image format.

PGM Binary format:
- A "magic number" for identifying the file type. A pgm image's magic number is the two characters "P5".
- Whitespace (blanks, TABs, CRs, LFs).
- A width, formatted as ASCII characters in decimal.
- Whitespace.
- A height, again in ASCII decimal.
- Whitespace.
- The maximum gray value (Maxval), again in ASCII decimal. Must be less than 65536, and more than zero.
- A single whitespace character (usually a newline).
- A raster of Height rows, in order from top to bottom. Each row consists of Width gray values, in order from left to right.
Each gray value is a number from 0 through Maxval, with 0 being black and Maxval being white.
Each gray value is represented in pure binary by either 1 or 2 bytes.
If the Maxval is less than 256, it is 1 byte. Otherwise, it is 2 bytes. The most significant byte is first.

PGM ASCII format:
- There is exactly one image in a file.
- The magic number is P2 instead of P5.
- Each pixel in the raster is represented as an ASCII decimal number (of arbitrary size).
- Each pixel in the raster has white space before and after it.
- There must be at least one character of white space between any two pixels, but there is no maximum.
- No line should be longer than 70 characters.


PPM Binary format:
- PPM’s Binary format is almost the same as PGM’s Binary format only the magic number is "P6" instead of "P5".

PPM ASCII format:
- There is exactly one image in a file.
- The magic number is P3 instead of P6.
- Each sample in the raster is represented as an ASCII decimal number (of arbitrary size).
- Each sample in the raster has white space before and after it. There must be at least one character of white space between any two samples, but there is no maximum. There is no particular separation of one pixel from another -- just the required separation between the blue sample of one pixel - from the red sample of the next pixel.
- No line should be longer than 70 characters.


Original picture:
![](https://github.com/phoenix6418/Image_effects/blob/master/contour/contour1_input.png)