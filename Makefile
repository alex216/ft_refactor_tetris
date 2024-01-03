FILES = tetris.c utils.c cmd_shape.c handle_key_press.c

tetris: $(FILES) tetris.h
	gcc $(FILES) -I tetris.h -lncurses -o tetris

re:
	rm -rf tetris
	make
