/* name : steg.c
 * author : matheo thomas
 * date : 28-11-23
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>
#include "steg.h"

png_infop info_ptr;
png_bytepp row_pointers;

void readPNG(char *filename){
	FILE *f = fopen(filename, "rb");

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);
	png_init_io(png_ptr, f);
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
	row_pointers = png_get_rows(png_ptr, info_ptr);

	png_destroy_read_struct(&png_ptr, NULL, NULL);
	fclose(f);
}


void writePNG(char *filename){
	FILE *f = fopen(filename, "wb");

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_init_io(png_ptr, f);
	png_set_rows(png_ptr, info_ptr, row_pointers);

	int w = png_get_image_width(png_ptr, info_ptr);
	int h = png_get_image_height(png_ptr, info_ptr);

	for(int i = 0; i < h; i++){
		png_bytep row = row_pointers[i];
		for(int j = 0; j < w; j++){
			png_bytep px = &(row[j*4]);

			for(int k = 0; k < 3; k++){
				if(px[k] == 255){
					px[k]--;

				} else {
					px[k]++;
				}
				// printf("%d ", px[k]);

				/*
				   if(px[k]%2 == 0){
				   printf("0");
				   } else {
				   printf("1");
				   }*/
			}
		}
	}

	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(f);
}

void decodePNG(char *filename, char *buffer){
	FILE *f = fopen(filename, "rb");

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);
	png_init_io(png_ptr, f);
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
	row_pointers = png_get_rows(png_ptr, info_ptr);

	int w = png_get_image_width(png_ptr, info_ptr);
	int h = png_get_image_height(png_ptr, info_ptr);

	int count = 0;
	for(int i = 0; i < h; i++){
		png_bytep row = row_pointers[i];
		for(int j = 0; j < w; j++){
			png_bytep px = &(row[j*4]);
			for(int k = 0; k < 3; k++){
				if(count < 10){
					if(px[k]%2 == 0){
						buffer[count] = 0;
					} else {
						buffer[count] = 1;
					}
				}
				count++;
			}
		}
	}


	printf("buffer : %s\n", buffer);


	png_destroy_read_struct(&png_ptr, NULL, NULL);
	fclose(f);
}


char *strToBin(char *s, char *buff){
	int n = strlen(s);
	//char buff[8*n+1];
	for(int i = 0; i < n; i++){
		for(int j = 7; j >= 0; j--){
			sprintf(&buff[8*i + 7-j], "%d", (s[i] >> j) & 1 ? 1 : 0);
		}
	}
	return buff;
}

char *binToStr(char *buff, char *s){
	char temp[9];
	int n = strlen(buff);
	for(int i = 0; i < n/8; i++){
		for(int j = 0; j < 8; j++){
			temp[j] = buff[8*i + j];
		}
		sprintf(&s[i], "%c", strtol(temp, 0, 2));
	}

	return s;
}

int main(void){
	printf("Steganography program.\n\nChoose an option :\n 0-Encode text\n 1-Decode image\n");
	int choice = 2;
	scanf("%d%*c", &choice);
	if(choice == 0){
		char *filename = (char *)malloc(255*sizeof(char));
		printf("Enter name of image : ");
		scanf("%s", filename);

		char *msg = (char *)malloc(255*sizeof(char));
		printf("Enter message : ");
		scanf("%s", msg);

		readPNG(filename);
		writePNG("../res/output.png");

	} else if(choice == 1){
		char *filename = (char *)malloc(255*sizeof(char));
		printf("Enter name of image : ");
		scanf("%s", filename);

		char buffer[255];
		decodePNG(filename, buffer);
		printf("Buffer : %s\n", buffer);
	} else {
		printf("Wrong value, exiting...\n");
	}
	/*
	   char *s = "Hello\0";

	   char *buff = (char *)malloc(strlen(s)*sizeof(char));
	   buff = strToBin(s, buff);
	   printf("buff : %s\n", buff);

	   char *s2 = (char *)malloc((strlen(buff)+1)*sizeof(char));
	   s2 = binToStr(buff, s2);
	   printf("s2 : %s\n", s2);
	   */
	return 0;
}

