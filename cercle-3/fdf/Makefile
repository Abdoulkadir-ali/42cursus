NAME = fdf

CC = clang
CFLAGS = -Wall -Wextra -Werror -I./includes -I./minilibx-linux -I./libft/includes -O3 -ffast-math -mavx -march=native
LDFLAGS = -L./minilibx-linux -lmlx -L./libft -lft -lX11 -lXext -lm -lpthread

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files organized by category
SRCS =	srcs/core/cleanup.c \
	srcs/camera/init.c \
	srcs/core/main.c \
	srcs/camera/controls/adjust.c \
	srcs/camera/controls/rotate/build.c \
	srcs/camera/controls/rotate/init.c \
	srcs/camera/controls/rotate/multiply.c \
	srcs/camera/controls/rotate/rotate.c \
	srcs/camera/controls/zoom.c \
	srcs/camera/projection/projection.c \
	srcs/camera/projection/basic.c \
	srcs/camera/projection/advanced.c \
	srcs/graphics/init.c \
	srcs/graphics/cache.c \
	srcs/graphics/draw/grid.c \
	srcs/graphics/draw/lines.c \
	srcs/graphics/draw/lines_helpers.c \
	srcs/graphics/draw/triangle.c \
	srcs/graphics/draw/spline.c \
	srcs/graphics/draw/scanlines.c \
	srcs/graphics/interpolate/lines.c \
	srcs/graphics/interpolate/splines.c \
	srcs/graphics/interpolate/triangle.c \
	srcs/graphics/z_processing/lines.c \
	srcs/graphics/z_processing/triangles.c \
	srcs/graphics/perspective/lines.c \
	srcs/graphics/frames/clear.c \
	srcs/color/create.c \
	srcs/color/transform.c \
	srcs/color/get.c \
	srcs/vectors/vec2/init.c \
	srcs/vectors/vec2/arithmetic.c \
	srcs/vectors/vec2/distance.c \
	srcs/vectors/vec2d/init.c \
	srcs/vectors/vec2d/arithmetic.c \
	srcs/vectors/vec2d/distance.c \
	srcs/vectors/vec3/init.c \
	srcs/vectors/vec3/arithmetic.c \
	srcs/vectors/vec3/distance.c \
	srcs/vectors/vec3d/init.c \
	srcs/vectors/vec3d/arithmetic.c \
	srcs/vectors/vec3d/distance.c \
	srcs/map/build/grid.c \
	srcs/map/init.c \
	srcs/map/read/loader.c \
	srcs/map/read/parser.c \
	srcs/map/read/select.c \
	srcs/map/style/style.c \
	srcs/map/style/themes.c \
	srcs/window/init.c \
srcs/core/init.c \
	srcs/events/mouse/events.c \
	srcs/events/mouse/move.c \
	srcs/events/mouse/handlers.c \
	srcs/events/mouse/press.c \
	srcs/events/keys/events.c \
	srcs/events/keys/handlers/combos/combo.c \
	srcs/events/keys/handlers/combos/helper.c \
	srcs/events/keys/handlers/flags/flag.c \
	srcs/events/keys/handlers/flags/helper.c \
	srcs/events/keys/handlers/flags/modifiers.c \
	srcs/events/keys/handlers/gui/gui.c \
	srcs/events/keys/handlers/map/map.c \
	srcs/events/keys/handlers/map/helper.c \
	srcs/events/keys/handlers/toggle/toggle.c \
	srcs/events/keys/handlers/view/camera.c \
	srcs/events/keys/handlers/view/helper.c \
	srcs/events/keys/init/helper.c \
	srcs/events/keys/init/init.c \
	srcs/events/keys/init/keys.c \
	srcs/events/keys/init/releases.c \
	srcs/events/gui/resize.c \
	srcs/events/init/init.c \
	srcs/events/hooks.c \
	srcs/events/init.c \
	srcs/gui/init.c \
	srcs/gui/redraw.c \
	srcs/gui/panel/panel.c \
	srcs/gui/print/put.c \
	srcs/gui/display/print/format.c \
	srcs/gui/display/layout.c \
	srcs/gui/display/sections/guide.c \
	srcs/gui/display/sections/movement.c \
	srcs/gui/display/sections/performance.c \
	srcs/gui/display/sections/style.c \
	srcs/gui/style/style.c \
	srcs/gui/style/select.c \


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
	@mkdir -p objs/graphics/draw
	@mkdir -p objs/graphics/interpolate
	@mkdir -p objs/graphics/z_processing
	@mkdir -p objs/graphics/perspective
	@mkdir -p objs/graphics/frames
	@mkdir -p objs/camera
	@mkdir -p objs/camera/controls
	@mkdir -p objs/camera/controls/rotate
	@mkdir -p objs/camera/projection
	@mkdir -p objs/color
	@mkdir -p objs/map
	@mkdir -p objs/map/build
	@mkdir -p objs/map/read
	@mkdir -p objs/map/style
	@mkdir -p objs/window
	@mkdir -p objs/events
	@mkdir -p objs/events/mouse
	@mkdir -p objs/events/keys
	@mkdir -p objs/events/keys/handlers
	@mkdir -p objs/events/keys/handlers/view
	@mkdir -p objs/events/keys/handlers/combos
	@mkdir -p objs/events/keys/handlers/map
	@mkdir -p objs/events/keys/handlers/toggle
	@mkdir -p objs/events/keys/handlers/flags
	@mkdir -p objs/vectors
	@mkdir -p objs/vectors/vec2
	@mkdir -p objs/vectors/vec2d
	@mkdir -p objs/vectors/vec3
	@mkdir -p objs/vectors/vec3d
	@mkdir -p objs/events/keys/handlers
	@mkdir -p objs/gui
	@mkdir -p objs/gui/controls
	@mkdir -p objs/gui/display/sections
	@mkdir -p objs/gui/panel
	@mkdir -p objs/gui/display/print
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