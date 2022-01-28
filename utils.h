// Copyright 2022 Dumitru Bianca Stefania - 312CA
#pragma once

#define COMMANDMAX 10
#define FILEMAX 100

#include "image_datatype.h"

// allocates memory for a matrix with *height* rows
// and double values
double **alloc_matrix(int width, int height);

// frees the memory of given matrix with *height* rows
void free_matrix(double ***matrix, int height);

// selects all the image
void select_all(image *img);
