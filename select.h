// Copyright 2022 Dumitru Bianca Stefania - 312CA
#pragma once

// checks whether after the word 'SELECT' is 'ALL' or
// a set of coordinates and select the image accordingly
void select_image(image * img);

// reads the string from stdin and checks whether it is a valid one
// (contains only digits, may begin with '-')
int make_number(int *x);
