# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/12 00:00:00 by abdoali           #+#    #+#              #
#    Updated: 2025/12/27 19:19:46 by abdoali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap
CHECKER		= checker

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I includes -I srcs/libft/includes

# Directories
SRC_DIR		= srcs/push_swap
OBJ_DIR		= obj
LIBFT_DIR	= srcs/libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Source files
SRCS		= parsing/stacks/check.c \
			  parsing/stacks/parser.c \
			  parsing/stacks/parse_int.c \
			  moves/push.c \
			  moves/rotate.c \
			  moves/reverse_rotate.c \
			  moves/swap.c \
			  helper/lst/ft_new.c \
			  helper/lst/ft_add_back.c \
			  helper/lst/ft_add_front.c \
			  helper/lst/ft_size.c \
			  helper/lst/ft_last.c \
			  helper/lst/ft_delone.c \
			  helper/lst/ft_clear.c \
			  helper/stacks/free.c \
			  helper/display/ft_print_lst.c \
			  helper/display/ft_puterr.c \
			  helper/display/ft_debug_stacks.c \
			  algo/cost/cost.c \
			  algo/cost/helper.c \
			  algo/target/target.c \
			  algo/target/helper.c \
			  algo/moves.c \
			  algo/sort/sort.c \
			  algo/sort/helper.c \
			  algo/push_swap.c

MAIN_SRCS	= main/main.c $(SRCS)
CHECKER_SRCS	= checker/checker.c parsing/moves/parser.c $(SRCS)

# Object files
MAIN_OBJ	= $(MAIN_SRCS:%.c=$(OBJ_DIR)/%.o)
CHECKER_OBJ	= $(CHECKER_SRCS:%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(LIBFT) -o $(NAME)

$(CHECKER): $(CHECKER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(CHECKER_OBJ) $(LIBFT) -o $(CHECKER)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME) $(CHECKER)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

bonus: $(CHECKER)

.PHONY: all clean fclean re bonus
