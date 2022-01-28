// Copyright 2022 Dumitru Bianca Stefania - 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "rotate.h"

void rotate_image(image *img)
{
	int angle, anglecpy;
	scanf("%d", &angle); // reads the rotation angle desired
	anglecpy = angle;

	// checks whether there is no image loaded
	if (!img->loaded) {
		fprintf(stdout, "No image loaded\n");
		return;
	}

	// checks whether the selection is square or the whole image is selected
	if (img->x2 - img->x1 != img->y2 - img->y1 && !(img->x2 - img->x1 ==
		img->width && img->y2 - img->y1 == img->height)) {
		fprintf(stdout, "The selection must be square\n");
		return;
	}

	// checks whether the rotation angle is a multiple of 90
	if (angle % 90 != 0 || abs(angle) > 360) {
		fprintf(stdout, "Unsupported rotation angle\n");
		return;
	}

	// transforms the negative angles to corresponding positive ones
	if (angle < 0)
		angle += 360;
	if (angle == 360)
		angle = 0;

	// rotates each channel(gray/red/green/blue) to the right
	// the desired number of times (angle/90)
	while (angle) {
		if (!img->color) {
			rotate_channel(&img->gray, &*img);
		} else {
			rotate_channel(&img->red, &*img);
			rotate_channel(&img->green, &*img);
			rotate_channel(&img->blue, &*img);
		}

		angle -= 90;

		// if we're rotating the whole image, swap width & height and
		// select all the rotated image
		if (img->x2 - img->x1 == img->width &&
			img->y2 - img->y1 == img->height) {
			int aux = img->width;
			img->width = img->height;
			img->height = aux;
			select_all(&*img);
		}
	}

	fprintf(stdout, "Rotated %d\n", anglecpy);
}

void rotate_channel(double ***channel, image *img)
{
	if (img->x2 - img->x1 == img->width && img->y2 - img->y1 == img->height)
		rotate_all(&*channel, &*img);
	else
		rotate_square(&*channel, &*img);
}

void rotate_square(double ***channel, image *img)
{
	// allocates space for a temporary matrix that
	// will be equal to the rotated selection
	double **tmp = (double **)alloc_matrix(img->x2 - img->x1,
										   img->y2 - img->y1);

	// values of tmp become the values of the selection
	for (int i = img->y1; i < img->y2; i++)
		for (int j = img->x1; j < img->x2; j++)
			tmp[i - img->y1][j - img->x1] = (*channel)[i][j];

	// transposes the matrix tmp
	for (int i = 0; i < img->y2 - img->y1; i++)
		for (int j = i + 1; j < img->x2 - img->x1; j++) {
			double aux = tmp[i][j];
			tmp[i][j] = tmp[j][i];
			tmp[j][i] = aux;
		}

	// mirrors the columns of matrix tmp
	for (int j = 0; j < (img->x2 - img->x1) / 2; j++)
		for (int i = 0; i < img->y2 - img->y1; i++) {
			double aux = tmp[i][j];
			tmp[i][j] = tmp[i][img->x2 - img->x1 - j - 1];
			tmp[i][img->x2 - img->x1 - j - 1] = aux;
		}

	// modifies the values in the original channel
	for (int i = img->y1; i < img->y2; i++)
		for (int j = img->x1; j < img->x2; j++)
			(*channel)[i][j] = tmp[i - img->y1][j - img->x1];

	// frees memory for matrix tmp
	free_matrix(&tmp, img->y2 - img->y1);
}

void rotate_all(double ***channel, image *img)
{
	// allocates space for a temporary matrix that
	// will be equal to the rotated channel
	double **tmp = (double **)alloc_matrix(img->height, img->width);

	// matrix tmp becomes the transpose of the channel
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++)
			tmp[j][i] = (*channel)[i][j];

	// mirrors the columns of matrix tmp
	for (int i = 0; i < img->width; i++)
		for (int j = 0; j < img->height / 2; j++) {
			double aux = tmp[i][j];
			tmp[i][j] = tmp[i][img->height - j - 1];
			tmp[i][img->height - j - 1] = aux;
		}

	// frees the memory for the given channel with dimesions w x h
	free_matrix(&*channel, img->height);

	// allocates memory for the channel with dimensions h x w
	*channel = alloc_matrix(img->height, img->width);

	// the original channel receives the values of its rotation
	for (int i = 0; i < img->width; i++)
		for (int j = 0; j < img->height; j++)
			(*channel)[i][j] = tmp[i][j];

	// frees memory for matrix tmp
	free_matrix(&tmp, img->width);
}

