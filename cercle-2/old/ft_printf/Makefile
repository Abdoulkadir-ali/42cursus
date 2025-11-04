# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/26 09:27:14 by abdali            #+#    #+#              #
#    Updated: 2025/10/22 23:01:23 by abdoali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
CC		=	@clang
CFLAGS	=	-Wall -Wextra -Werror
IFLAGS	=	-Iinc -Ilibft/inc
MK		=	@mkdir -p
RM		=	@rm -rf
CLEAR	=	@clear
SRCS_DIR	:=	src
ALL_SRCS	:=	ft_printf.c
SRCS		:=	$(ALL_SRCS:%=$(SRCS_DIR)/%)

OBJS_DIR	:=	.objs
OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

LIBFT_PATH	= ./libft
LIBFT_NAME	= ./libft/libft.a

all: $(LIBFT_NAME) $(NAME)

$(OBJS_DIR)/%.o: %.c
	$(MK) $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	
$(LIBFT_NAME):
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJS) 
	@ar rcsT $(NAME) $(OBJS) $(LIBFT_NAME)

clean:
	@make clean -C $(LIBFT_PATH)
	$(RM) $(OBJS_DIR)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re: fclean all