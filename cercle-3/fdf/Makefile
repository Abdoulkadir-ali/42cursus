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
	srcs/graphics/graphics.c \
	srcs/graphics/lines/draw.c \
	srcs/graphics/lines/draw_line.c \
	srcs/graphics/splines/spline.c \
	srcs/graphics/triangles/triangle.c \
	srcs/camera/controls/adjust.c \
	srcs/camera/controls/rotate.c \
	srcs/camera/controls/zoom.c \
	srcs/camera/projection/projection.c \
	srcs/camera/projection/basic.c \
	srcs/camera/projection/advanced.c \
	srcs/color/color.c \
	srcs/color/interpolate.c \
	srcs/map/build/grid.c \
	srcs/map/read/loader.c \
	srcs/map/read/select.c \
	srcs/map/style/style.c \
	srcs/events/mouse/mouse_events.c \
	srcs/events/mouse/mouse_move.c \
	srcs/events/keys/key_events.c \
	srcs/events/keys/key_handlers.c \
	srcs/gui/panel/panel.c \
	srcs/gui/print/put.c \
	srcs/gui/print/format.c \
	srcs/gui/display/displays.c \
	srcs/gui/style/style.c \
	srcs/gui/style/select.c \
	srcs/gui/controls/guide.c \
	srcs/gui/controls/keyboard.c \
	srcs/gui/controls/mouse.c \


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
	@mkdir -p objs/graphics/lines
	@mkdir -p objs/graphics/splines
	@mkdir -p objs/graphics/triangles
	@mkdir -p objs/camera
	@mkdir -p objs/camera/controls
	@mkdir -p objs/camera/projection
	@mkdir -p objs/color
	@mkdir -p objs/map
	@mkdir -p objs/map/build
	@mkdir -p objs/map/read
	@mkdir -p objs/map/style
	@mkdir -p objs/events
	@mkdir -p objs/events/mouse
	@mkdir -p objs/events/keys
	@mkdir -p objs/gui
	@mkdir -p objs/gui/controls
	@mkdir -p objs/gui/display
	@mkdir -p objs/gui/panel
	@mkdir -p objs/gui/print
	@mkdir -p objs/gui/style
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