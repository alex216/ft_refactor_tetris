FILES = main.c utils.c \
		cmds_for_shape.c \
		control_key_press.c \
		global_variables.c \
		move_down.c

tetris: $(FILES) tetris.h
	gcc $(FILES) -I tetris.h -lncurses -o tetris

re:
	rm -rf tetris
	make
