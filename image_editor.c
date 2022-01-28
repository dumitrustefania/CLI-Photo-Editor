// Copyright 2022 Dumitru Bianca Stefania - 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "image_datatype.h"
#include "utils.h"
#include "load.h"
#include "select.h"
#include "rotate.h"
#include "crop.h"
#include "apply.h"
#include "save.h"

int main(void)
{
	char command[COMMANDMAX];
	image img;
	img.loaded = 0;
	int exit = 0;

	while (exit == 0) { // while EXIT command was not given yet
		// reads the first word of the command in order
		// to call the specific function
		scanf("%s", command);

		if (!strcmp(command, "LOAD")) {
			load_image(&img);
			}
		else if (!strcmp(command, "SELECT")) {
			select_image(&img);
			}
		else if (!strcmp(command, "ROTATE")) {
			rotate_image(&img);
			}
		else if (!strcmp(command, "CROP")) {
			crop_image(&img);
			}
		else if (!strcmp(command, "APPLY")) {
			filter_image(&img);
			}
		else if (!strcmp(command, "SAVE")) {
			save_image(&img);
			}
		else if (!strcmp(command, "EXIT")) {
			if (!img.loaded)
				fprintf(stdout, "No image loaded");
			else
				free_image(&img);
			exit = 1;
		} else {
			fprintf(stdout, "Invalid command\n");
			// reads the remaining characters until encountering \n
			char dummy;
			while (scanf("%c", &dummy))
				if (dummy == '\n')
					break;
		}
	}
	return 0;
}
