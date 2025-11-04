# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 00:00:00 by abdali            #+#    #+#              #
#    Updated: 2025/11/04 09:48:44 by abdoali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

OBJDIR = objs

INCLUDES = -I.

SRCS = ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	   ft_tolower.c ft_toupper.c \
	   ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	   ft_atoi.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
	   ft_lstaddback.c ft_lstaddfront.c ft_lstclear.c ft_lstdelone.c \
	   ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
	   ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	   ft_memmove.c ft_memrchr.c ft_memrcpy.c ft_memset.c \
	   ft_itoa.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c \
	   ft_strmapi.c ft_strndup.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
	   ft_substr.c \
	   ft_striteri.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)


all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) -r $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

bonus: $(NAME)
