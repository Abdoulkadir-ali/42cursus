# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdali <abdali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/26 09:27:14 by abdali            #+#    #+#              #
#    Updated: 2024/04/29 09:39:08 by abdali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC		=	@clang
CFLAGS	=	-Wall -Wextra -Werror
IFLAGS	=	-Iinc
MK		=	@mkdir -p
RM		=	@rm -rf
FILE	=	$(shell ls -lR src/ | grep -F .c | wc -l)
CMP		=	1
CLEAR	=	@clear

# CHECK
CHECK_DIR	:=	check
SRC_CHECK	:=	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c
CHECK		:=	$(SRC_CHECK:%=$(CHECK_DIR)/%)

#LIST
LIST_DIR	:=	list
SRC_LIST	:=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
LIST		:=	$(SRC_LIST:%=$(LIST_DIR)/%)

# MEMORY
MEM_DIR		:=	memory
SRC_MEM		:=	ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c
MEM			:=	$(SRC_MEM:%=$(MEM_DIR)/%)

# PRINT
PRINT_DIR	:=	print
SRC_PRINT	:=	ft_putchar.c ft_putchar_fd.c ft_putendl_fd.c ft_puthexa_u.c ft_putnbr_base.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_putunbr_base.c
PRINT		:=	$(SRC_PRINT:%=$(PRINT_DIR)/%)

# STRING
STRING_DIR	:=	string
SRC_STRING	:=	ft_atoi.c ft_itoa.c ft_nbrlen_base.c ft_split.c ft_strcapitalize.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_unbrlen_base.c
STRING		:=	$(SRC_STRING:%=$(STRING_DIR)/%)

#ALL SOURCES
SRCS_DIR	:=	src
ALL_SRCS	:=	$(CHECK) $(LIST) $(MEM) $(PRINT) $(STRING)
SRCS		:=	$(ALL_SRCS:%=$(SRCS_DIR)/%)

# OBJECTS
OBJS_DIR	:=	.objs
OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	$(MK) $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o  $@

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
