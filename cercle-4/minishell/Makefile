NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 -Iincludes -Ipackages/libft/includes
RM          = rm -f

SRCS_DIR    = srcs
OBJS_DIR    = objs

# List all source files. 
# main.c is currently empty, and tokenizer.c has a main function for testing.
# Only one main function should exist in the final build.
SRCS        = srcs/exec/exec_tree.c \
	srcs/exec/path_finder.c \
	srcs/exec/pipe.c \
	srcs/lib/str.c \
	srcs/lib/debug.c \
	srcs/parsing/env_expand.c \
	srcs/parsing/ast_builder.c \
	srcs/parsing/tokenizer.c \
	srcs/reader/loop.c \
	srcs/utils/error.c \
	srcs/utils/memory.c \
	srcs/core/main.c
# srcs/main.c # Uncomment when ready to use main.c instead of tokenizer.c's main

OBJS        = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

LIBFT_DIR   = packages/libft
LIBFT       = $(LIBFT_DIR)/libft.a
LIBS        = -L$(LIBFT_DIR) -lft -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) -r $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
