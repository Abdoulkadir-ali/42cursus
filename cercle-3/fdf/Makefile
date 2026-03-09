NAME = fdf

CC = clang
MAKEFLAGS += j8
CFLAGS = -Wall -Wextra -I. -I./includes -I./minilibx-linux -I./libft/includes -O3 -ffast-math -Wno-nan-infinity-disabled
LDFLAGS = -L./minilibx-linux -lmlx -L./libft -lft -lX11 -lXext -lm -lpthread

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = $(shell find srcs -name "*.c" | sort)
OBJS = $(SRCS:srcs/%.c=objs/%.o)

MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@echo "Building MinilibX..."
	@make -C $(MLX_DIR) 2>/dev/null || make -C $(MLX_DIR)

objs:
	@mkdir -p $(dir $(OBJS))

objs/%.o: srcs/%.c includes/fdf.h | objs
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(NAME) created successfully!"

clean:
	@echo "Cleaning object files..."
	@rm -rf objs
	@make -C $(MLX_DIR) clean 2>/dev/null || true
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

generate: $(LIBFT)
	@echo "Building fdf_gen..."
	@$(CC) $(CFLAGS) srcs/geometry/map/generator/main.c srcs/geometry/map/generator/noise.c srcs/geometry/map/generator/builder.c srcs/geometry/map/generator/writer.c $(LDFLAGS) -o fdf_gen
	@echo "Generator created successfully!"

.PHONY: all clean fclean re objs generate