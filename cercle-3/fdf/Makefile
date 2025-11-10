NAME = fdf

CC = clang
CFLAGS = -Wall -Wextra -Werror -I./includes -I./minilibx-linux -I./libft/includes -O3
LDFLAGS = -L./minilibx-linux -lmlx -L./libft -lft -lX11 -lXext -lm -lpthread

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files organized by category
SRCS =	srcs/core/main.c \
	srcs/core/init.c \
	srcs/core/cleanup.c \
	srcs/graphics/draw.c \
	srcs/graphics/draw_line.c \
	srcs/graphics/window.c \
	srcs/graphics/spline.c \
	srcs/graphics/triangle.c \
	srcs/graphics/map_style.c \
	srcs/graphics/map_style_apply.c \
	srcs/math/rotate.c \
	srcs/math/zoom.c \
	srcs/camera/adjust.c \
	srcs/color/color.c \
	srcs/color/interpolate.c \
	srcs/world/map.c \
	srcs/world/map_loader.c \
	srcs/world/select.c \
	srcs/input/buttons.c \
	srcs/events/mouse_events.c \
	srcs/events/mouse_move.c \
	srcs/events/key_events.c \
	srcs/events/key_handlers.c \
	srcs/gui/gui_panel.c \
	srcs/gui/gui_controls.c \
	srcs/gui/gui_displays.c \
	srcs/gui/gui_style.c \
	srcs/projection/projection.c \
	srcs/projection/basic_projections.c \
	srcs/projection/advanced_projections.c

# Object files in objs directory
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

# Create necessary subdirectories in objs
objs:
	@mkdir -p objs/core
	@mkdir -p objs/graphics
	@mkdir -p objs/math
	@mkdir -p objs/camera
	@mkdir -p objs/color
	@mkdir -p objs/world
	@mkdir -p objs/input
	@mkdir -p objs/events
	@mkdir -p objs/gui
	@mkdir -p objs/projection

# Compile object files
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

.PHONY: all clean fclean re objs