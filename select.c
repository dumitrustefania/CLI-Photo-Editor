// Copyright 2022 Dumitru Bianca Stefania - 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "select.h"

void select_image(image *img)
{
	char cmd[COMMANDMAX];
	scanf("%s", cmd);

	// checks if the command is SELECT ALL
	if (!strcmp(cmd, "ALL")) {
		if (img->loaded) {
			select_all(&*img);
			fprintf(stdout, "Selected ALL\n");
		} else {
			fprintf(stdout, "No image loaded\n");
			return;
		}

		return;
	}

	// reads the coordinates of the selection
	int x1, y1, x2, y2;
	x1 = atoi(cmd);

	// for each coordinate, checks whether it is a valid string of digits
	if (!make_number(&y1)) {
		fprintf(stdout, "Invalid command\n");
		return;
	}

	if (!make_number(&x2)) {
		fprintf(stdout, "Invalid command\n");
		return;
	}

	if (!make_number(&y2)) {
		fprintf(stdout, "Invalid command\n");
		return;
	}

	// makes sure the coordinates are in ascending order
	if (x1 > x2) {
		int aux = x1;
		x1 = x2;
		x2 = aux;
	}

	if (y1 > y2) {
		int aux = y1;
		y1 = y2;
		y2 = aux;
	}

	// checks whether there is an image loaded
	if (!img->loaded) {
		fprintf(stdout, "No image loaded\n");
		return;
	}

	// checks whether the coordinates for the selection are valid
	if (x1 >= 0 && y1 >= 0 && x2 <= img->width && y2 <= img->height &&
		x1 < x2 && y1 < y2) {
		// memorises the selection
		img->x1 = x1;
		img->y1 = y1;
		img->x2 = x2;
		img->y2 = y2;
		fprintf(stdout, "Selected %d %d %d %d\n", x1, y1, x2, y2);
	} else {
		fprintf(stdout, "Invalid set of coordinates\n");
		}
}

int make_number(int *x)
{
	char chr;
	scanf("%c", &chr);

	if (chr == '\n') // if there's no string to read
		return 0;

	char s[COMMANDMAX];
	scanf("%s", s);
	// if the string does not start with a digit or '-', it is not valid
	if (!isdigit(s[0]) && s[0] != '-')
		return 0;

	// checks whether all the next characters are digits
	for (unsigned int i = 1; i < strlen(s); i++)
		if (!isdigit(s[i]))
			return 0;
	// transforms the read string of digits into an integer
	*x = atoi(s);
	return 1;
}

