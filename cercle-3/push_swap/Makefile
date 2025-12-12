# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/12 00:00:00 by abdoali           #+#    #+#              #
#    Updated: 2025/12/12 22:47:15 by abdoali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap
CHECKER		= checker

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I includes -I srcs/libft/includes

# Directories
SRC_DIR		= srcs/push_swap
OBJ_DIR		= obj
LIBFT_DIR	= srcs/libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Common source files (shared by multiple targets)
COMMON_SRCS	= parsing/stacks/check.c \
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
			  helper/display/ft_puterr.c

ALGO_SRCS	= algo/cost.c \
			  algo/target.c \
			  algo/moves.c \
			  algo/sort.c \
			  algo/push_swap.c

# Main program sources
MAIN_SRCS	= main/main.c $(COMMON_SRCS) $(ALGO_SRCS)

# Checker sources
CHECKER_SRCS = checker/checker.c \
			   parsing/moves/parser.c \
			   $(COMMON_SRCS) $(ALGO_SRCS)

# Test sources
TEST_PARSER_SRCS = parsing/stacks/test.c \
				   parsing/stacks/check.c \
				   parsing/stacks/parser.c \
				   parsing/stacks/parse_int.c \
				   helper/lst/ft_new.c \
				   helper/lst/ft_add_back.c \
				   helper/lst/ft_add_front.c \
				   helper/lst/ft_clear.c \
				   helper/lst/ft_delone.c \
				   helper/lst/ft_size.c \
				   helper/lst/ft_last.c \
				   helper/stacks/free.c \
				   helper/display/ft_puterr.c

TEST_MOVE_SRCS = moves/test.c \
				 parsing/moves/parser.c \
				 $(COMMON_SRCS) $(ALGO_SRCS)

TEST_ALGO_SRCS = algo/tests/main.c \
				 parsing/moves/parser.c \
				 $(COMMON_SRCS) $(ALGO_SRCS)

TEST_COST_SRCS = algo/tests/cost.c \
				 parsing/moves/parser.c \
				 $(COMMON_SRCS) $(ALGO_SRCS)

TEST_TARGET_SRCS = algo/tests/target.c \
				   parsing/moves/parser.c \
				   $(COMMON_SRCS) $(ALGO_SRCS)

# Object files
MAIN_OBJ		= $(MAIN_SRCS:%.c=$(OBJ_DIR)/%.o)
CHECKER_OBJ		= $(CHECKER_SRCS:%.c=$(OBJ_DIR)/%.o)
TEST_PARSER_OBJ	= $(TEST_PARSER_SRCS:%.c=$(OBJ_DIR)/%.o)
TEST_MOVE_OBJ	= $(TEST_MOVE_SRCS:%.c=$(OBJ_DIR)/%.o)
TEST_ALGO_OBJ	= $(TEST_ALGO_SRCS:%.c=$(OBJ_DIR)/%.o)
TEST_COST_OBJ	= $(TEST_COST_SRCS:%.c=$(OBJ_DIR)/%.o)
TEST_TARGET_OBJ	= $(TEST_TARGET_SRCS:%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(LIBFT) -o $(NAME)

$(CHECKER): $(CHECKER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(CHECKER_OBJ) $(LIBFT) -o $(CHECKER)

$(LIBFT):
	@make -C $(LIBFT_DIR)

# Test targets
test: tests/parser tests/move tests/algo tests/cost tests/target

tests/parser: $(TEST_PARSER_OBJ) $(LIBFT)
	@mkdir -p tests
	$(CC) $(CFLAGS) $(TEST_PARSER_OBJ) $(LIBFT) -o $@

tests/move: $(TEST_MOVE_OBJ) $(LIBFT)
	@mkdir -p tests
	$(CC) $(CFLAGS) $(TEST_MOVE_OBJ) $(LIBFT) -o $@

tests/algo: $(TEST_ALGO_OBJ) $(LIBFT)
	@mkdir -p tests
	$(CC) $(CFLAGS) $(TEST_ALGO_OBJ) $(LIBFT) -o $@

tests/cost: $(TEST_COST_OBJ) $(LIBFT)
	@mkdir -p tests
	$(CC) $(CFLAGS) $(TEST_COST_OBJ) $(LIBFT) -o $@

tests/target: $(TEST_TARGET_OBJ) $(LIBFT)
	@mkdir -p tests
	$(CC) $(CFLAGS) $(TEST_TARGET_OBJ) $(LIBFT) -o $@

# Clean targets
clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME) $(CHECKER)
	@rm -rf tests
	@make fclean -C $(LIBFT_DIR)

re: fclean all

bonus: $(CHECKER)

.PHONY: all clean fclean re test bonus
