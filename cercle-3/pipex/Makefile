# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/09 00:00:00 by abdali            #+#    #+#              #
#    Updated: 2025/11/09 16:19:48 by abdoali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I./includes -I./srcs/libft
RM			= rm -rf

SRCS_DIR	= srcs/pipex
OBJS_DIR	= objs
LIBFT_DIR	= srcs/libft
LIBFT		= $(LIBFT_DIR)/libft.a
GNL_DIR		= srcs/gnl

SRCS		= access.c \
			  cmd.c \
			  exit.c \
			  here_doc.c \
			  io.c \
			  main.c \
			  parser.c \
			  pipes.c \
			  pipex.c \
			  process.c

GNL_SRCS	= get_next_line.c \
			  get_next_line_utils.c

SRCS_PATH	= $(addprefix $(SRCS_DIR)/, $(SRCS))
GNL_PATH	= $(addprefix $(GNL_DIR)/, $(GNL_SRCS))
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
GNL_OBJS	= $(addprefix $(OBJS_DIR)/, $(GNL_SRCS:.c=.o))

HEADER		= includes/pipex.h

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS) $(GNL_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(GNL_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	$(RM) $(OBJS_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
