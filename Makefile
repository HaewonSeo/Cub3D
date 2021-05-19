# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/05 22:19:27 by haseo             #+#    #+#              #
#    Updated: 2021/05/19 19:58:57 by haseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3D

CC			= gcc
CFLAGS 		= -Wall -Wextra -Werror
RM			= rm -f

SRCS_LIST	=	00_cub3d.c \
				01_read_elements.c \
				02_read_map.c \
				03_valid_cub.c \
				04_set_cub.c \
				05_start_game.c \
				06_raycast.c \
				07_raycast_dda.c \
				08_raycast_wall.c \
				09_raycast_sprite.c \
				10_save_screenshot.c

LIBFT_DIR	= ./libft
LIBFT		= ./libft.a
INC_DIR		= ./inc
SRC_DIR		= ./src
OBJ_DIR		= ./obj

SRCS		= $(addprefix $(SRC_DIR)/, $(SRCS_LIST))
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS_LIST:.c=.o))

OS = $(shell uname -s)
ifeq ($(OS), Darwin)
	MLX_DIR = ./mlx
	LIB = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	MLX_DIR = ./minilibx-linux
	LIB = -L $(MLX_DIR) -lmlx -lm -lXext -lX11
endif

all:		libft $(NAME)

bonus:		all

libft:
			$(MAKE) -C $(LIBFT_DIR) bonus

%.o: %.c
			mkdir -p $(OBJ_DIR)
			$(CC) -c $(CFLAGS) -o $@ $< -I$(INC_DIR)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(LIB) -o $@ $^

clean:
			$(MAKE) -C $(LIBFT_DIR) clean
			$(RM) $(OBJS)
			rmdir $(OBJ_DIR)

fclean:		clean
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(RM) $(NAME)


re:			fclean all

.PHONY: 	libft all clean fclean re bonus
