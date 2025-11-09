# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/09 00:00:00 by abdali            #+#    #+#              #
#    Updated: 2025/11/09 16:55:35 by abdoali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= gnl.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I./includes -I../libft/includes
AR			= ar rcs
RM			= rm -rf

SRCS_DIR	= srcs
OBJS_DIR	= objs
INCLUDES	= includes

SRCS		= get_next_line.c \
			  get_next_line_utils.c

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

HEADER		= $(INCLUDES)/get_next_line.h

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

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
