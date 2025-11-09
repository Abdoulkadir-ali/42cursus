# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/09 00:00:00 by abdali            #+#    #+#              #
#    Updated: 2025/11/09 14:41:24 by abdoali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I./includes
RM			= rm -rf

SRCS_DIR	= srcs
OBJS_DIR	= objs

SRCS		= main.c \
			  helper.c \
			  errors.c \
			  pipex.c

SRCS_PATH	= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

HEADER		= includes/pipex.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
