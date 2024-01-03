tetris: tetris.c
	gcc tetris.c utils.c cmd_shape.c -I tetris.h -lncurses -o tetris
