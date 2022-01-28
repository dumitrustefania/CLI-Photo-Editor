// Copyright 2022 Dumitru Bianca Stefania - 312CA
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

double **alloc_matrix(int width, int height)
{
	double **matrix = (double **)malloc(height * sizeof(double *));

	// check if malloc() failed
	if (!matrix) {
		fprintf(stderr, "malloc() failed\n");
		exit(-1);
	}

	for (int i = 0; i < height; i++) {
		// allocate space for every row
		matrix[i] = malloc(width * sizeof(double));

		// check if malloc() failed
		if (!matrix[i]) {
			for (int j = 0; j < i; j++)
				// free the memory allocated for the previous rows
				free(matrix[j]);
			// free the matrix itself
			free(matrix);
			fprintf(stderr, "malloc() failed\n");
			exit(-1);
		}
	}

	return matrix;
}

void free_matrix(double ***matrix, int height)
{	// free all the rows of the matrix
	for (int i = 0; i < height; i++)
		free((*matrix)[i]);

	//free the matrix itself
	free(*matrix);
}

void select_all(image *img)
{
	img->x1 = 0;
	img->y1 = 0;
	img->x2 = img->width;
	img->y2 = img->height;
}
