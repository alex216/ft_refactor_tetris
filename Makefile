# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 13:37:51 by yliu              #+#    #+#              #
#    Updated: 2024/01/06 15:55:53 by kaksano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR	=	./src
SRCS		=	main.c \
				utils.c \
				cmds_for_shape.c \
				control_key_press.c \
				global_variables.c \
				proceed_update_score_and_map.c

SRCS_PATH	:=	$(addprefix $(SRCS_DIR)/, $(SRCS))

tetris: $(SRCS_PATH) ./inc/tetris.h
	gcc $(CFLAGS) $(SRCS_PATH) -I./inc/ -lncurses -o tetris

re:
	rm -rf tetris
	make
