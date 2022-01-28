// Copyright 2022 Dumitru Bianca Stefania - 312CA
#pragma once

// crops the given image, keeping just the previously
// selected area
void crop_image(image * img);

// crops each channel
void crop_channel(image *img, double ***channel);
