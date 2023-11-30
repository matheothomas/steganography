/* name : steg.h
 * author : matheo thomas
 * date : 28-11-23
 */

#ifndef steg_h 
#define steg_h


/* Functions definitions */

// Reads the content of the given file.
void readPNG(char *filename);

// Writes the content of a read file in the given file.
void writePNG(char *filename, char *buffer);

// Reads the content of the filename and decodes the hidden message.
void decodePNG(char *filename, char *buffer);

// Converts a string into its corresponding ASCII binary code.
char *strToBin(char *s, char *buff);

// Converts a ASCII binary code into its corresponding string.
char *binToStr(char *buff, char *s);


#endif

