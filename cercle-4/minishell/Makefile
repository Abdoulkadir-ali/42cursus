NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 -Iincludes -Ipackages/libft/includes
RM          = rm -f

SRCS_DIR    = srcs
OBJS_DIR    = objs

# List all source files. 
# main.c is currently empty, and tokenizer.c has a main function for testing.
# Only one main function should exist in the final build.
SRCS        = srcs/core/main.c \
	srcs/core/reader.c \
	srcs/core/signals.c \
	srcs/core/global.c \
	srcs/exec/builtins/builtins.c \
	srcs/exec/builtins/cd.c \
	srcs/exec/builtins/echo.c \
	srcs/exec/builtins/env.c \
	srcs/exec/builtins/exit.c \
	srcs/exec/builtins/export.c \
	srcs/exec/builtins/pwd.c \
	srcs/exec/builtins/unset.c \
	srcs/exec/env/print.c \
	srcs/exec/env/process.c \
	srcs/exec/env/set.c \
	srcs/exec/env/utils.c \
	srcs/exec/exec/path_finder.c \
	srcs/exec/exec/pipe.c \
	srcs/exec/exec/tree.c \
	srcs/exec/heredoc/gen.c \
	srcs/exec/heredoc/heredoc.c \
	srcs/exec/heredoc/read.c \
	srcs/lib/debug.c \
	srcs/lib/str.c \
	srcs/parsing/ast/builder.c \
	srcs/parsing/ast/cmd.c \
	srcs/parsing/ast/redirections.c \
	srcs/parsing/ast/utils.c \
	srcs/parsing/env/expand/expand.c \
	srcs/parsing/env/expand/split.c \
	srcs/parsing/env/expand/tokens.c \
	srcs/parsing/env/expand/match.c \
	srcs/parsing/env/expand/utils.c \
	srcs/parsing/env/expand/vars.c \
	srcs/parsing/env/wildcard/matcher.c \
	srcs/parsing/env/wildcard/array.c \
	srcs/parsing/tokenizer/tokenizer.c \
	srcs/parsing/tokenizer/syntax.c
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

test: all
	@mkdir -p tests
	@chmod +x tests/stress_test.sh
	@bash tests/stress_test.sh

.PHONY: all clean fclean re test
