// Copyright 2022 Dumitru Bianca Stefania - 312CA
#pragma once

// reads the desired filter to be applied and applies it
void filter_image(image * img);

// applies the filter to each channel(RGB) of the image
void apply(image *img, int filter);

// function for clamping the value of a pixel
double clamp(double sum);
