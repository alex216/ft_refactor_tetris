# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 13:37:51 by yliu              #+#    #+#              #
#    Updated: 2024/01/23 15:03:03 by yliu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR	=	./src
CLFAGS		=	-Wall -Wextra -Werror
SRCS		=	main.c \
				process_tetris.c \
				utils.c \
				cmds_for_block.c \
				control_key_press.c \
				global_variables.c \
				proceed_update_score_and_map.c

SRCS_PATH	:=	$(addprefix $(SRCS_DIR)/, $(SRCS))

tetris: $(SRCS_PATH) ./inc/tetris.h
	gcc $(CFLAGS) $(SRCS_PATH) -I./inc/ -lncurses -o tetris

re:
	rm -rf tetris
	make
