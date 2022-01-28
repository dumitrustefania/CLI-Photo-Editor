// Copyright 2022 Dumitru Bianca Stefania - 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "load.h"

void load_image(image *img)
{
	// frees the image that is already loaded
	if (img->loaded)
		free_image(&*img);

	char filename[FILEMAX];
	scanf("%s", filename);

	FILE *fin = fopen(filename, "r");

	// checks whether the file was opened successfully
	if (!fin) {
		img->loaded = 0;
		fprintf(stdout, "Failed to load %s\n", filename);
		return;
	}

	// removes possible comments and reads the header of the image
	remove_comments(fin);
	fscanf(fin, "%s", img->type);
	remove_comments(fin);
	fscanf(fin, "%d%d", &img->width, &img->height);
	remove_comments(fin);
	fscanf(fin, "%d", &img->maxval);
	remove_comments(fin);

	// allocates memory for the image
	alloc_image(&*img);

	// checks whether the image is ascii or binary and loads it accordingly
	if ((!strcmp(img->type, "P2") || !strcmp(img->type, "P3"))) {
		load_ascii(&*img, fin);
	} else {
		// if it's a binary image, opens the file as binary
		FILE *finb = fopen(filename, "rb");

		if (!finb) {
			fprintf(stdout, "Failed to load %s\n", filename);
			return;
		}

		// sets the position indicator at the beggining of the pixels matrix
		fseek(finb, ftell(fin), SEEK_SET);
		load_binary(&*img, finb);
	}

	fprintf(stdout, "Loaded %s\n", filename);

	img->loaded = 1;
	fclose(fin);

	select_all(&*img);
}

void load_binary(image *img, FILE *fin)
{
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++) {
			if (!strcmp(img->type, "P5")) { // grayscale
				unsigned char a;
				fread(&a, sizeof(unsigned char), 1, fin);
				img->gray[i][j] = (double)a;
			} else { // RGB
				unsigned char a, b, c;
				fread(&a, sizeof(unsigned char), 1, fin);
				fread(&b, sizeof(unsigned char), 1, fin);
				fread(&c, sizeof(unsigned char), 1, fin);

				img->red[i][j] = (double)a;
				img->green[i][j] = (double)b;
				img->blue[i][j] = (double)c;
			}
		}
	fclose(fin);
}

void load_ascii(image *img, FILE *fin)
{
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++)
			if (!strcmp(img->type, "P2")) // grayscale
				fscanf(fin, "%lf", &img->gray[i][j]);
			else // RGB
				fscanf(fin, "%lf%lf%lf", &img->red[i][j], &img->green[i][j],
					   &img->blue[i][j]);
}

void alloc_image(image *img)
{
	if (!strcmp(img->type, "P2") || !strcmp(img->type, "P5")) {
		img->color = 0;
		img->gray = alloc_matrix(img->width, img->height);
	} else {
		img->color = 1;
		img->red = alloc_matrix(img->width, img->height);
		img->green = alloc_matrix(img->width, img->height);
		img->blue = alloc_matrix(img->width, img->height);
	}
}

void free_image(image *img)
{
	// first frees the rows
	for (int i = 0; i < img->height; i++) {
		if (!strcmp(img->type, "P2") || !strcmp(img->type, "P5")) {
			free(img->gray[i]);
		} else {
			free(img->red[i]);
			free(img->green[i]);
			free(img->blue[i]);
		}
	}

	// then, frees the memory for the matrix itself
	if (!strcmp(img->type, "P2") || !strcmp(img->type, "P5")) {
		free(img->gray);
	} else {
		free(img->red);
		free(img->green);
		free(img->blue);
	}
}

void remove_comments(FILE *fin)
{
	char chr;
	fscanf(fin, "%c", &chr);
	if (chr == '\n')
		fscanf(fin, "%c", &chr);
	if (chr == '#')
		while (chr != '\n')
			fscanf(fin, "%c", &chr);
	else
		fseek(fin, -1, SEEK_CUR);
}
