# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/12 00:00:00 by abdoali           #+#    #+#              #
#    Updated: 2026/03/10 04:22:21 by abdoali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap
CHECKER		= checker

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I./includes -I./packages/libft/includes
RM			= rm -rf

MAKEFLAGS	+= -j8
SRC_DIR		= srcs/push_swap
OBJ_DIR		= objs
LIBFT_DIR	= packages/libft
LIBFT		= $(LIBFT_DIR)/libft.a
HEADER		= includes/push_swap.h

SRCS		= $(shell find $(SRC_DIR) -name "*.c" | sort)
COMMON_SRCS	= $(filter-out \
	$(SRC_DIR)/main/main.c \
	$(SRC_DIR)/checker/checker.c \
	$(SRC_DIR)/parsing/stacks/main.c \
	$(SRC_DIR)/parsing/moves/parser.c, $(SRCS))
MAIN_SRCS	= $(COMMON_SRCS) $(SRC_DIR)/main/main.c
CHECKER_SRCS	= $(COMMON_SRCS) $(SRC_DIR)/checker/checker.c \
			  $(SRC_DIR)/parsing/moves/parser.c

MAIN_OBJS	= $(MAIN_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CHECKER_OBJS	= $(CHECKER_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

bonus: $(CHECKER)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(LIBFT) -o $(NAME)

$(CHECKER): $(LIBFT) $(CHECKER_OBJS)
	$(CC) $(CFLAGS) $(CHECKER_OBJS) $(LIBFT) -o $(CHECKER)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(CHECKER)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
