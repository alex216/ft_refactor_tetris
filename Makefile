# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 13:37:51 by yliu              #+#    #+#              #
#    Updated: 2024/01/05 13:37:53 by yliu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR = ./src
SRCS =	main.c \
		utils.c \
		cmds_for_shape.c \
		control_key_press.c \
		global_variables.c \
		move_down.c
SRCS_PATH := $(addprefix $(SRCS_DIR)/, $(SRCS))

tetris: $(SRCS_PATH) ./inc/tetris.h
	gcc $(CFLAGS) $(SRCS_PATH) -I ./inc/tetris.h -lncurses -o tetris

re:
	rm -rf tetris
	make
