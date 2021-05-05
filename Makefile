# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/05 22:19:27 by haseo             #+#    #+#              #
#    Updated: 2021/05/06 02:36:34 by haseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3D

CC			= gcc
CFLAGS 		= -Wall -Wextra -Werror
RM			= rm -f

SRCS_LIST	= cub3d.c\

LIBFT_DIR	= ./libft
LIBFT		= ./libft.a
INC_DIR		= ./inc
SRCS_DIR	= ./src

OS = $(shell uname -s)

ifeq ($(OS), Darwin)
	MLX_DIR = ./mlx
	LIB = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	MLX_DIR = ./minilibx-linux
	LIB = -L $(MLX_DIR) -lmlx -lm -lXext -lX11
endif

SRCS		= $(addprefix $(SRCS_DIR)/, $(SRCS_LIST))
OBJS		= $(SRCS:.c=.o)


all:		libft $(NAME)

bonus:		all

libft:
			$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(LIB) -o $@ $<

%.o: %.c
			$(CC) -c $(CFLAGS) -o $@ $< -I$(INC_DIR)

clean:
			$(MAKE) -C $(LIBFT_DIR) clean
			$(RM) $(OBJS)

fclean:		clean
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY: 	libft all clean fclean re bonus
