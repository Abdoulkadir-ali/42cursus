# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 00:00:00 by abdali            #+#    #+#              #
#    Updated: 2025/11/09 16:54:07 by abdoali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -rf

SRCS_DIR	= srcs
OBJS_DIR	= objs
INCLUDES	= includes

INCLUDES_FLAG = -I$(INCLUDES)

CHAR_DIR	= $(SRCS_DIR)/char
FD_DIR		= $(SRCS_DIR)/fd
INT_DIR		= $(SRCS_DIR)/int
LST_DIR		= $(SRCS_DIR)/lst
MEM_DIR		= $(SRCS_DIR)/mem
STR_DIR		= $(SRCS_DIR)/str

CHAR_SRCS	= ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isdigit.c \
			  ft_isprint.c ft_tolower.c ft_toupper.c
FD_SRCS		= ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c
INT_SRCS	= ft_atoi.c
LST_SRCS	= ft_lstaddback.c ft_lstaddfront.c ft_lstclear.c ft_lstdelone.c \
			  ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
MEM_SRCS	= ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
			  ft_memmove.c ft_memrchr.c ft_memrcpy.c ft_memset.c
STR_SRCS	= ft_itoa.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
			  ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
			  ft_strncmp.c ft_strndup.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
			  ft_substr.c

CHAR_PATH	= $(addprefix $(CHAR_DIR)/, $(CHAR_SRCS))
FD_PATH		= $(addprefix $(FD_DIR)/, $(FD_SRCS))
INT_PATH	= $(addprefix $(INT_DIR)/, $(INT_SRCS))
LST_PATH	= $(addprefix $(LST_DIR)/, $(LST_SRCS))
MEM_PATH	= $(addprefix $(MEM_DIR)/, $(MEM_SRCS))
STR_PATH	= $(addprefix $(STR_DIR)/, $(STR_SRCS))

SRCS		= $(CHAR_PATH) $(FD_PATH) $(INT_PATH) $(LST_PATH) $(MEM_PATH) $(STR_PATH)
OBJS		= $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

HEADER		= $(INCLUDES)/libft.h

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER) | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES_FLAG) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus
