// Copyright 2022 Dumitru Bianca Stefania - 312CA
#pragma once

#include "image_datatype.h"

// reads the file to load the image from, then loads
// the header and pixel values of the image
void load_image(image * img);

// loads the matrix of pixels from the binary file
void load_binary(image *img, FILE *fin);

// loads the matrix of pixels from the plain file
void load_ascii(image *img, FILE *fin);

// allocates memory for each matrix of pixels
void alloc_image(image *img);

// frees the allocated memory for each matrix of pixels
void free_image(image *img);

// removes the lines that contain comments
void remove_comments(FILE *fin);
