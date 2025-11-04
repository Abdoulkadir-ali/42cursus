# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 00:00:00 by abdali            #+#    #+#              #
#    Updated: 2025/10/17 00:22:18 by abdoali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library name
NAME = libft.a

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# Directories
SRCDIR = srcs
OBJDIR = objs

# Include flags
INCLUDES = -I.

# Source files by category
CHAR_SRCS = ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_tolower.c ft_toupper.c

FD_SRCS = ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c

INT_SRCS = ft_atoi.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c

LST_SRCS = ft_lstaddback.c ft_lstaddfront.c ft_lstclear.c ft_lstdelone.c \
		   ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

MEM_SRCS = ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		   ft_memmove.c ft_memrchr.c ft_memrcpy.c ft_memset.c

STR_SRCS = ft_itoa.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c \
		   ft_strmapi.c ft_strndup.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
		   ft_substr.c

VOID_SRCS = ft_striteri.c

# Add directory prefixes to source files
SRCS = $(addprefix $(SRCDIR)/char/, $(CHAR_SRCS)) \
	   $(addprefix $(SRCDIR)/fd/, $(FD_SRCS)) \
	   $(addprefix $(SRCDIR)/int/, $(INT_SRCS)) \
	   $(addprefix $(SRCDIR)/lst/, $(LST_SRCS)) \
	   $(addprefix $(SRCDIR)/mem/, $(MEM_SRCS)) \
	   $(addprefix $(SRCDIR)/str/, $(STR_SRCS)) \
	   $(addprefix $(SRCDIR)/void/, $(VOID_SRCS))

# Object files
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Colors for pretty output
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m # No Color

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Creating library $(NAME)...$(NC)"
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(NC)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@$(RM) -r $(OBJDIR)
	@echo "$(GREEN)✓ Object files cleaned!$(NC)"

fclean: clean
	@echo "$(RED)Cleaning library...$(NC)"
	@$(RM) $(NAME)
	@echo "$(GREEN)✓ Library cleaned!$(NC)"

re: fclean all
	@echo "$(GREEN)✓ Rebuild complete!$(NC)"

# Bonus rule (if you want to compile only list functions)
bonus: $(NAME)

# Help rule
help:
	@echo "$(GREEN)Available targets:$(NC)"
	@echo "  $(YELLOW)all$(NC)         - Build the library"
	@echo "  $(YELLOW)clean$(NC)       - Remove object files"
	@echo "  $(YELLOW)fclean$(NC)      - Remove object files and library"
	@echo "  $(YELLOW)re$(NC)          - Clean and rebuild"
	@echo "  $(YELLOW)bonus$(NC)       - Build with bonus functions"
	@echo "  $(YELLOW)help$(NC)        - Show this help message"
	@echo "  $(YELLOW)info$(NC)        - Show compilation info"

# Show compilation info
info:
	@echo "$(GREEN)Compilation Info:$(NC)"
	@echo "  $(YELLOW)Compiler:$(NC) $(CC)"
	@echo "  $(YELLOW)Flags:$(NC) $(CFLAGS)"
	@echo "  $(YELLOW)Includes:$(NC) $(INCLUDES)"
	@echo "  $(YELLOW)Sources:$(NC) $(words $(SRCS)) files"
	@echo "  $(YELLOW)Library:$(NC) $(NAME)"

.PHONY: all clean fclean re bonus test test_char test_fd test_int test_lst \
		test_mem test_str test_void clean_tests help info
