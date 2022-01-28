// Copyright 2022 Dumitru Bianca Stefania - 312CA
#pragma once

// reads the desired rotation angle and performs right
// rotations on the selected area of the image
void rotate_image(image * img);

// applies the square rotation alg. or the whole image
// rotation alg. on the given channel
void rotate_channel(double ***channel, image *img);

// rotates the square selection of the given channel
void rotate_square(double ***channel, image *img);

// rotates the whole channel to the right
void rotate_all(double ***channel, image *img);
