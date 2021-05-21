# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/05 22:19:27 by haseo             #+#    #+#              #
#    Updated: 2021/05/20 23:29:36 by haseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= cub3D

# ----------------------------------
# Compile flag
# ----------------------------------
CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
CFLAGS			+= -g3 -fsanitize=address
# CFLAGS			+= -g

# ----------------------------------
# Command
# ----------------------------------

RM				= rm -f
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

SRCS_LIST		= 00_cub3d.c \
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
	MLX_DIR = ./mlx
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
					@$(ECHO) "$(GREEN)[Success]\t $(ORANGE)Create $@$(NOCOLOR)"

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
					@$(RMDIR) $(OBJ_DIR)
					@$(ECHO) "$(GREEN)[Success]\t $(RED)Remove $(OBJ_DIR)$(NOCOLOR)"

fclean:			clean
					@$(MAKE) -C $(LIBFT_DIR) fclean
					@$(RM) $(NAME)
					@$(ECHO) "$(GREEN)[Success]\t $(RED)Remove $(NAME)$(NOCOLOR)"


re:				fclean all

.PHONY: 		all bonus $(LIBFT) $(NAME) clean fclean re
