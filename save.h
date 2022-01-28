// Copyright 2022 Dumitru Bianca Stefania - 312CA
#pragma once
#include "image_datatype.h"

// reads the file where the image should be saved,
// then saves it accordingly, either as plain or binary
void save_image(image * img);

// saves the pixel values in the plain file
// by rounding their values to an integer
void save_ascii(image *img, FILE *fout);

// saves the pixel values in the plain file
// by rounding their values to an unsigned char
void save_binary(image *img, FILE *fout);

