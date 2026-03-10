# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/09 00:00:00 by abdali            #+#    #+#              #
#    Updated: 2026/03/10 04:07:26 by abdoali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I./includes -I./packages/libft/includes
RM			= rm -rf

MAKEFLAGS	+= -j8
SRCS_DIR	= srcs
OBJS_DIR	= objs
LIBFT_DIR	= packages/libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		= $(shell find $(SRCS_DIR) -name "*.c" | sort)
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
HEADER		= includes/pipex.h

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER) | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	$(RM) $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
