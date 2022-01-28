// Copyright 2022 Dumitru Bianca Stefania - 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "save.h"

void save_image(image *img)
{
	// reads the name of the file
	char filename[FILEMAX];
	scanf("%s", filename);
	char chr;
	scanf("%c", &chr);

	// checks if there is no image loaded
	if (!img->loaded) {
		fprintf(stdout, "No image loaded\n");
		// if the word 'ascii' was after the filename, reads it as dummy input
		if (chr == ' ') {
			char dummy[COMMANDMAX];
			scanf("%s", dummy);
		}
		return;
	}

	FILE * fout;
	fout = fopen(filename, "wt"); // opens the file in writing mode

	if (!fout) {
		fprintf(stdout, "Failed to open / create %s", filename);
		// if the word 'ascii' was after the filename, reads it as dummy input
		if (chr == ' ') {
			char dummy[COMMANDMAX];
			scanf("%s", dummy);
		}
		return;
	}

	int saved_binary = 0;
	if (chr == ' ') {
		// if first character is after filename is ' ', expects 'ascii' or '\n'
		char chr;
		scanf("%c", &chr);

		if (chr == '\n') { // no 'ascii' present
			saved_binary = 1;
		} else { // 'ascii' file !
			char word[COMMANDMAX];
			scanf("%s", word); // reads the word 'ascii'

			if (img->color) // prints the new magic word
				fprintf(fout, "%s\n", "P3");
			else
				fprintf(fout, "%s\n", "P2");

			// prints the header of the image
			fprintf(fout, "%d %d\n%d\n", img->width, img->height, img->maxval);
			// saves the matrix in the plain file
			save_ascii(&*img, fout);
			fclose(fout); // closes the file
		}
	} else { // no space after filename => binary file
		saved_binary = 1;
	}

	if (saved_binary) {
		if (img->color) // prints the new magic word
			fprintf(fout, "%s\n", "P6");
		else
			fprintf(fout, "%s\n", "P5");

		// prints the header of the image
		fprintf(fout, "%d %d\n%d\n", img->width, img->height, img->maxval);
		// closes the plain file
		fclose(fout);

		// opens the file as binary append
		FILE *fout = fopen(filename, "ab");
		if (!fout) {
			fprintf(stdout, "Failed to open / create %s", filename);
			return;
		}
		// saves the matrix in the binary file
		save_binary(&*img, fout);
		fclose(fout); // closes the binary file
	}
	fprintf(stdout, "Saved %s\n", filename);
}

void save_ascii(image *img, FILE *fout)
{
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++)
			if (!img->color) {
				fprintf(fout, "%d ", (int)round(img->gray[i][j]));
			} else {
				fprintf(fout, "%d ", (int)round(img->red[i][j]));
				fprintf(fout, "%d ", (int)round(img->green[i][j]));
				fprintf(fout, "%d ", (int)round(img->blue[i][j]));
			}
		fprintf(fout, "\n");
	}
}

void save_binary(image *img, FILE *fout)
{
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++)
			if (!img->color) {
				unsigned char a;
				a = (unsigned char)round(img->gray[i][j]);
				fwrite(&a,  sizeof(unsigned char), 1, fout);
			} else {
				unsigned char a, b, c;
				a = (unsigned char)round(img->red[i][j]);
				b = (unsigned char)round(img->green[i][j]);
				c = (unsigned char)round(img->blue[i][j]);
				fwrite(&a, sizeof(unsigned char), 1, fout);
				fwrite(&b, sizeof(unsigned char), 1, fout);
				fwrite(&c, sizeof(unsigned char), 1, fout);
			}
}

