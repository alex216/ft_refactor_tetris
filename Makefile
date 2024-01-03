tetris: tetris.c utils.c cmd_shape.c tetris.h
	gcc tetris.c utils.c cmd_shape.c -I tetris.h -lncurses -o tetris

re:
	rm -rf tetris
	make
