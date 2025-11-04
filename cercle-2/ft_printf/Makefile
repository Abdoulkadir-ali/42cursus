# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 00:00:00 by abdali            #+#    #+#              #
#    Updated: 2025/11/04 10:23:08 by abdoali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library name
NAME = libftprintf.a

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# Directories
SRC_DIR = srcs/printf
LIBFT_DIR = srcs/libft
BONUS_DIR = $(SRC_DIR)/bonus
LIBFT = $(LIBFT_DIR)/libft.a
OBJDIR = obj

# Include flags
INCLUDES = -I$(SRC_DIR) -I$(LIBFT_DIR)

# Source files
SRCS = $(SRC_DIR)/ft_printf.c \
       $(SRC_DIR)/ft_handle.c

# Bonus source files
BONUS_SRCS = $(BONUS_DIR)/ft_handle_bonus.c \
             $(BONUS_DIR)/ft_how_much.c \
             $(BONUS_DIR)/ft_prefixes.c \
             $(BONUS_DIR)/ft_suffixes.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJDIR)/bonus/%.o)

# Colors for pretty output
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m # No Color

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Creating ft_printf library...$(NC)"
	@cp $(LIBFT) $(NAME)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(NC)"

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(NC)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✓ libft built successfully!$(NC)"

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/bonus/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(OBJDIR)/bonus
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@$(RM) -r $(OBJDIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)✓ Object files cleaned!$(NC)"

fclean: clean
	@echo "$(RED)Cleaning library...$(NC)"
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)✓ Library cleaned!$(NC)"

re: fclean all
	@echo "$(GREEN)✓ Rebuild complete!$(NC)"

# Bonus rule
bonus: $(LIBFT) $(OBJS) $(BONUS_OBJS)
	@echo "$(YELLOW)Creating ft_printf library with bonus...$(NC)"
	@cp $(LIBFT) $(NAME)
	@$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "$(GREEN)✓ $(NAME) with bonus created successfully!$(NC)"

# Test rule
test: $(NAME)
	@echo "$(YELLOW)Creating test program...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) main.c $(NAME) -o test_printf
	@echo "$(GREEN)✓ Test program created! Run ./test_printf$(NC)"

.PHONY: all clean fclean re bonus test