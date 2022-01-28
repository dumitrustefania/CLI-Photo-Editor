# Copyright 2022 Dumitru Bianca Stefania - 312CA

CFLAGS=-Wall -Wextra -std=c99 

build:
	gcc $(CFLAGS) utils.c load.c rotate.c save.c crop.c select.c apply.c image_editor.c -lm -o image_editor 

pack:
	zip -FSr 312CA_DumitruBiancaStefania_Tema3.zip README Makefile *.c *.h

clean:
	rm -f image_editor

.PHONY: pack clean
