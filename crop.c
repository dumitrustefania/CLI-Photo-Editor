// Copyright 2022 Dumitru Bianca Stefania - 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "crop.h"

void crop_image(image *img)
{
	// checks if there is no image loaded
	if (!img->loaded) {
		fprintf(stdout, "No image loaded\n");
		return;
	}

	// crops each channel
	if (!img->color) {
		crop_channel(&*img, &img->gray);
	} else {
		crop_channel(&*img, &img->red);
		crop_channel(&*img, &img->green);
		crop_channel(&*img, &img->blue);
	}

	// changes the width & height of the image
	img->width = img->x2 - img->x1;
	img->height = img->y2 - img->y1;

	// selects all image
	select_all(&*img);
	fprintf(stdout, "Image cropped\n");
}

void crop_channel(image *img, double ***channel)
{
	int new_width = img->x2 - img->x1;
	int new_height = img->y2 - img->y1;

	// allocates space for the new cropped channel
	double **new_channel = alloc_matrix(new_width, new_height);

	// the new channel receives the specific values in the selection
	for (int i = 0; i < new_height; i++)
		for (int j = 0; j < new_width; j++)
			new_channel[i][j] = (*channel)[i + img->y1][j + img->x1];

	// frees memory for the old channel
	free_matrix(&*channel, img->height);

	// allocates memory for the new channel that will have
	// a smaller no. of pixels
	(*channel) = alloc_matrix(new_width, new_height);

	// the channel is given its new values
	for (int i = 0; i < new_height; i++)
		for (int j = 0; j < new_width; j++)
			(*channel)[i][j] = new_channel[i][j];

	// frees the temporary matrix used for cropping
	free_matrix(&new_channel, new_height);
}
