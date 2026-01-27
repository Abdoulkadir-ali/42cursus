NAME        = fdf

MINILIBX_DIR = packages/minilibx-linux
MINILIBX    = $(MINILIBX_DIR)/libmlx.a
LIBFT_DIR   = packages/libft
LIBFT       = $(LIBFT_DIR)/libft.a
LIBS        = -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -lreadline -lm -lz -lXext -lX11



CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 -Iincludes -Ipackages/libft/includes -I$(MINILIBX_DIR) -DDEBUG_EXTENDER -g
RM          = rm -f
SRCS_DIR    = srcs
OBJS_DIR    = objs
SRCS        = $(shell find $(SRCS_DIR) -name "*.c")
OBJS        = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))


all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_DIR)

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
