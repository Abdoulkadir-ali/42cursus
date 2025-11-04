# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 00:00:00 by abdali            #+#    #+#              #
#    Updated: 2025/10/24 11:36:48 by abdoali          ###   ########.fr        #
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
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
OBJDIR = obj

# Include flags
INCLUDES = -I. -I$(LIBFT_DIR)

# Source files
SRCS = ft_printf.c ft_handle.c

# Object files
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

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

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
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

# Test rule
test: $(NAME)
	@echo "$(YELLOW)Creating test program...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) main.c $(NAME) -o test_printf
	@echo "$(GREEN)✓ Test program created! Run ./test_printf$(NC)"

.PHONY: all clean fclean re test