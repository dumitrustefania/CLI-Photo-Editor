// Copyright 2022 Dumitru Bianca Stefania - 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "apply.h"
#include "filter_values.h"

void filter_image(image *img)
{
	// checks if there is an image loaded
	if (!img->loaded) {
		fprintf(stdout, "No image loaded\n");
		// reads EDGE/SHARPED/BLUR/GAUSSIAN_BLUR keywords as dummy input
		char dummy;
		while (scanf("%c", &dummy))
			if (dummy == '\n')
				break;
		return;
	}

	// checks if the command is just APPLY\n => invalid
	char dummy;
	scanf("%c", &dummy);
	if (dummy == '\n') {
		fprintf(stdout, "Invalid command\n");
		return;
	}

	// reads the filter to be applied and calls the function to apply it
	char cmd[30];
	scanf("%s", cmd);
	if (!strcmp(cmd, "EDGE")) {
		apply(&*img, 0);

	} else if (!strcmp(cmd, "SHARPEN")) {
		apply(&*img, 1);

	} else if (!strcmp(cmd, "BLUR")) {
		apply(&*img, 2);

	} else if (!strcmp(cmd, "GAUSSIAN_BLUR")) {
		apply(&*img, 3);
	} else {
		fprintf(stdout, "APPLY parameter invalid\n");
		return;
	}
}

void apply(image *img, int filter)
{
	// checks if the image is grayscale
	if (!img->color) {
		fprintf(stdout, "Easy, Charlie Chaplin\n");
		return;
	}

	// allocates memory for each of the new channel matrices
	double **new_red = alloc_matrix(img->x2 - img->x1, img->y2 - img->y1);
	double **new_blue = alloc_matrix(img->x2 - img->x1, img->y2 - img->y1);
	double **new_yellow = alloc_matrix(img->x2 - img->x1, img->y2 - img->y1);

	for (int i = img->y1; i < img->y2; i++)
		for (int j = img->x1; j < img->x2; j++) {
			double sum1 = 0, sum2 = 0, sum3 = 0;

			// if we're not on the edge of the matrix
			if (i != 0 && j != 0 && i != img->height - 1 && j != img->width - 1)
				for (int i1 = -1; i1 <= 1; i1++)
					for (int j1 = -1; j1 <= 1; j1++) {
						// multiply neighbour values to the specific values of
						// the filter's kernel, then sums all these 9 values
						sum1 += img->red[i + i1][j + j1] *
								filter_values[filter][i1 + 1][j1 + 1];
						sum2 += img->green[i + i1][j + j1] *
								filter_values[filter][i1 + 1][j1 + 1];
						sum3 += img->blue[i + i1][j + j1] *
								filter_values[filter][i1 + 1][j1 + 1];
					}

			// each pixel becomes the clamped resulting sum
			new_red[i - img->y1][j - img->x1] = clamp(sum1);
			new_blue[i - img->y1][j - img->x1] = clamp(sum2);
			new_yellow[i - img->y1][j - img->x1] = clamp(sum3);
		}

	// the initial values of the channels are changed to the new ones
	for (int i = img->y1; i < img->y2; i++)
		for (int j = img->x1; j < img->x2; j++)
			if (i != 0 && j != 0 && i != img->height - 1 &&
				j != img->width - 1) {
				img->red[i][j] = new_red[i - img->y1][j - img->x1];
				img->green[i][j] = new_blue[i - img->y1][j - img->x1];
				img->blue[i][j] = new_yellow[i - img->y1][j - img->x1];
			}

	// frees the temporary matrices
	free_matrix(&new_red, img->y2 - img->y1);
	free_matrix(&new_blue, img->y2 - img->y1);
	free_matrix(&new_yellow, img->y2 - img->y1);

	char filter_applied[4][20] = { "EDGE", "SHARPEN", "BLUR", "GAUSSIAN_BLUR" };
	fprintf(stdout, "APPLY %s done\n", filter_applied[filter]);
}

double clamp(double sum)
{
	if (sum < 0)
		sum = 0;
	else if (sum > 255)
		sum = 255;
	return sum;
}
