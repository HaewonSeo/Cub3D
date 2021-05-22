# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/05 22:19:27 by haseo             #+#    #+#              #
#    Updated: 2021/05/22 20:16:31 by haseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= cub3D

# ----------------------------------
# Compile flag
# ----------------------------------
CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
# CFLAGS			+= -g3 -fsanitize=address
# CFLAGS			+= -g

# ----------------------------------
# Command
# ----------------------------------

RM				= rm -rf
MKDIR			= mkdir -p
RMDIR			= rmdir
ECHO			= echo

# ----------------------------------
# Echo Color
# ----------------------------------

NOCOLOR			= \033[0m
RED				= \033[0;31m
GREEN			= \033[0;32m
ORANGE			= \033[0;33m
BLUE			= \033[0;34m
PURPLE			= \033[0;35m
CYAN			= \033[0;36m
LIGHTGRAY		= \033[0;37m
DARKGRAY		= \033[1;30m
LIGHTRED		= \033[1;31m
LIGHTGREEN		= \033[1;32m
YELLOW			= \033[1;33m
LIGHTBLUE		= \033[1;34m
LIGHTPURPLE		= \033[1;35m
LIGHTCYAN		= \033[1;36m
WHITE			= \033[1;37m

# ----------------------------------
# Source & Object file
# ----------------------------------

SRCS_LIST		=	cub3d.c \
					read_elements.c \
					read_map.c \
					valid_cub.c \
					set_cub.c \
					start_game.c \
					raycast.c \
					raycast_dda.c \
					raycast_wall.c \
					raycast_sprite.c \
					save_screenshot.c

SRCS			= $(addprefix $(SRC_DIR)/, $(SRCS_LIST))
OBJS			= $(addprefix $(OBJ_DIR)/, $(SRCS_LIST:.c=.o))

# ----------------------------------
# Directory
# ----------------------------------

LIBFT_DIR		= ./libft
INC_DIR			= ./inc
SRC_DIR			= ./src
OBJ_DIR			= ./obj

# ----------------------------------
# Library
# ----------------------------------

LIBFT			= libft.a

OS 				= $(shell uname -s)
ifeq ($(OS), Darwin)
	MLX_DIR = ./minilibx_opengl_20191021
	LIB = -lmlx -framework OpenGL -framework AppKit
else
	MLX_DIR = ./minilibx-linux
	LIB = -lmlx -lm -lXext -lX11
endif

LIB += -lft

# ----------------------------------
# Rules
# ----------------------------------

all:			$(OBJ_DIR) $(LIBFT) $(NAME)

bonus:			all

$(OBJ_DIR):
					@$(MKDIR) $@
					@$(ECHO) "$(GREEN)[Success]\t $(ORANGE)Create $(OBJ_DIR)$(NOCOLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
					@$(CC) -c $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -o $@ $<
					@$(ECHO) "$(GREEN)[Success]\t $(ORANGE)Create $@$(NOCOLOR)"

$(LIBFT):
					@$(MAKE) -C $(LIBFT_DIR) bonus
					@$(ECHO) "$(GREEN)[Success]\t $(ORANGE)Create $@ \t$(NOCOLOR)"

$(NAME):		$(OBJS)
					@$(CC) $(CFLAGS) -L$(MLX_DIR) -L$(LIBFT_DIR) -o $@ $^ $(LIB)
					@$(ECHO) "$(GREEN)[Success]\t $(ORANGE)Create $@$(NOCOLOR)"

clean:
					@$(MAKE) -C $(LIBFT_DIR) clean
					@$(RM) $(OBJS)
					@$(RM) $(OBJ_DIR)
					@$(ECHO) "$(GREEN)[Success]\t $(RED)Remove $(OBJ_DIR)$(NOCOLOR)"

fclean:			clean
					@$(MAKE) -C $(LIBFT_DIR) fclean
					@$(RM) $(NAME)
					@$(ECHO) "$(GREEN)[Success]\t $(RED)Remove $(NAME)$(NOCOLOR)"

re:				fclean all

.PHONY: 		all bonus clean fclean re
