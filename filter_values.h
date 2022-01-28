// Copyright 2022 Dumitru Bianca Stefania - 312CA
// used for applying filters by multiplying pixel
// values to the specific values of the kernels
double filter_values[4][4][4] = {
	//EDGE
	{{-1, -1, -1},
	{-1,  8, -1},
	{-1, -1, -1}},

	//SHARPEN
	{{0, -1,  0},
	{-1, 5, -1},
	{0, -1,  0}},

	//BLUR
	{{1.0 / 9, 1.0 / 9, 1.0 / 9},
	{1.0 / 9, 1.0 / 9, 1.0 / 9},
	{1.0 / 9, 1.0 / 9, 1.0 / 9}},

	//GAUSSIAN BLUR
	{{1.0 / 16, 2.0 / 16, 1.0 / 16},
	{2.0 / 16, 4.0 / 16, 2.0 / 16},
	{1.0 / 16, 2.0 / 16, 1.0 / 16}}
};
