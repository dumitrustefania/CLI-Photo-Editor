// Copyright 2022 Dumitru Bianca Stefania - 312CA
#pragma once

typedef struct image {
	double **gray, **red, **green, **blue; // matrices for gray/RGB channels
	int width, height; // width & height of the image
	int color;	// grayscale(0) or RGB(1) image
	int x1, y1, x2, y2;	// current selection
	char type[3];	// may be P2, P3, P5 or P6
	int loaded;	// check if there's any image loaded
	int maxval;	// max ascii value of pixels
}

image;
