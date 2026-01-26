NAME        = minishell
CC          = cc
MAKEFLAGS	+= -j4
CFLAGS      = -Wall -Wextra -Werror -g3 -Iincludes -Ipackages/libft/includes -DDEBUG_EXTENDER
RM          = rm -f

SRCS_DIR    = srcs
OBJS_DIR    = objs

SRCS        = $(shell find $(SRCS_DIR) -name "*.c")

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

test: re
	bash ~/tools/

.PHONY: all clean fclean re test
