NAME = fdf

CC = clang
CFLAGS = -Wall -Wextra -Werror -I./includes -I./minilibx-linux -I./libft/includes -O3 -ffast-math -mavx -march=native
LDFLAGS = -L./minilibx-linux -lmlx -L./libft -lft -lX11 -lXext -lm -lpthread

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files organized by category
SRCS =	srcs/core/cleanup.c \
	srcs/core/init.c \
	srcs/core/main.c \
	srcs/render/camera/init.c \
	srcs/render/camera/controls/adjust.c \
	srcs/render/camera/controls/rotate/build.c \
	srcs/render/camera/controls/rotate/init.c \
	srcs/render/camera/controls/rotate/multiply.c \
	srcs/render/camera/controls/rotate/rotate.c \
	srcs/render/camera/controls/zoom.c \
	srcs/render/camera/controls/center.c \
	srcs/render/pipeline.c \
	srcs/render/stages/projections.c \
	srcs/render/stages/culling.c \
	srcs/render/optimization/lines.c \
	srcs/render/optimization/triangles.c \
	srcs/geometry/matrix.c \
	srcs/geometry/tesselation/tesselation.c \
	srcs/geometry/tesselation/manager.c \
	srcs/geometry/vectors/vec2/init.c \
	srcs/geometry/vectors/vec2/arithmetic.c \
	srcs/geometry/vectors/vec2/distance.c \
	srcs/geometry/vectors/vec2d/init.c \
	srcs/geometry/vectors/vec2d/arithmetic.c \
	srcs/geometry/vectors/vec2d/distance.c \
	srcs/geometry/vectors/vec3/init.c \
	srcs/geometry/vectors/vec3/arithmetic.c \
	srcs/geometry/vectors/vec3/distance.c \
	srcs/geometry/vectors/vec3d/init.c \
	srcs/geometry/vectors/vec3d/arithmetic.c \
	srcs/geometry/vectors/vec3d/distance.c \
	srcs/geometry/vectors/vecu2/init.c \
	srcs/geometry/vectors/vecu2/arithmetic.c \
	srcs/geometry/vectors/vecu2/distance.c \
	srcs/geometry/vectors/vecu3/init.c \
	srcs/geometry/vectors/vecu3/arithmetic.c \
	srcs/geometry/vectors/vecu3/distance.c \
	srcs/geometry/map/build/grid.c \
	srcs/geometry/map/build/helper.c \
	srcs/geometry/map/build/minmax.c \
	srcs/geometry/map/init.c \
	srcs/geometry/map/read/loader.c \
	srcs/geometry/map/read/parser.c \
	srcs/geometry/map/read/helper.c \
	srcs/geometry/map/read/select.c \
	srcs/geometry/map/style/style.c \
	srcs/geometry/map/style/themes.c \
	srcs/graphics/init/init.c \
	srcs/graphics/cache/cache.c \
	srcs/graphics/cache/helper.c \
	srcs/graphics/draw/grid/grid.c \
	srcs/graphics/draw/grid/threads.c \
	srcs/graphics/draw/grid/quad.c \
	srcs/graphics/draw/grid/segment.c \
	srcs/graphics/draw/lines/draw.c \
	srcs/graphics/draw/lines/helper.c \
	srcs/graphics/draw/lines/bresenham/bresenham.c \
	srcs/graphics/draw/lines/bresenham/helper.c \
	srcs/graphics/draw/triangle/draw.c \
	srcs/graphics/draw/triangle/helper.c \
	srcs/graphics/draw/triangle/rasterizer/rasterizer.c \
	srcs/graphics/draw/triangle/rasterizer/helper.c \
	srcs/graphics/draw/splines/draw.c \
	srcs/graphics/draw/triangle/scanlines/draw.c \
	srcs/graphics/draw/triangle/scanlines/helper.c \
	srcs/graphics/frames/clear.c \
	srcs/graphics/frames/helper.c \
	srcs/color/create.c \
	srcs/color/transform.c \
	srcs/color/get.c \
	srcs/window/init.c \
	srcs/events/mouse/move.c \
	srcs/events/mouse/handlers.c \
	srcs/events/mouse/press.c \
	srcs/events/keys/handlers/combos/combo.c \
	srcs/events/keys/handlers/combos/helper.c \
	srcs/events/keys/handlers/flags/flag.c \
	srcs/events/keys/handlers/flags/helper.c \
	srcs/events/keys/handlers/flags/modifiers.c \
	srcs/events/keys/handlers/gui/gui.c \
	srcs/events/keys/handlers/map/map.c \
	srcs/events/keys/handlers/toggle/tesselation.c \
	srcs/events/keys/handlers/toggle/points.c \
	srcs/events/keys/handlers/toggle/toggle.c \
	srcs/events/keys/handlers/view/camera.c \
	srcs/events/keys/handlers/view/helper.c \
	srcs/events/keys/handlers/view/fisheye.c \
	srcs/events/keys/init/helper.c \
	srcs/events/keys/init/init.c \
	srcs/events/keys/init/keys.c \
	srcs/events/keys/init/releases.c \
	srcs/events/gui/resize.c \
	srcs/events/init/init.c \
	srcs/gui/init.c \
	srcs/gui/redraw.c \
	srcs/gui/panel/panel.c \
	srcs/gui/print/put.c \
	srcs/gui/print/format.c \
	srcs/gui/layout/layout.c \
	srcs/gui/layout/guide.c \
	srcs/gui/layout/movement.c \
	srcs/gui/layout/performance.c \
	srcs/gui/layout/style.c \
	srcs/gui/layout/theme.c \
	srcs/gui/layout/utils.c \
	


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
	@mkdir -p objs/graphics/init
	@mkdir -p objs/graphics/cache
	@mkdir -p objs/graphics/draw
	@mkdir -p objs/graphics/draw/grid
	@mkdir -p objs/graphics/draw/grid/draw
	@mkdir -p objs/graphics/draw/lines
	@mkdir -p objs/graphics/draw/lines/bresenham
	@mkdir -p objs/graphics/draw/triangle
	@mkdir -p objs/graphics/draw/triangle/rasterizer
	@mkdir -p objs/graphics/draw/triangle/scanlines
	@mkdir -p objs/graphics/draw/splines
	@mkdir -p objs/graphics/frames
	@mkdir -p objs/render
	@mkdir -p objs/render/camera
	@mkdir -p objs/render/camera/controls
	@mkdir -p objs/render/camera/controls/rotate
	@mkdir -p objs/render/optimization
	@mkdir -p objs/render/stages
	@mkdir -p objs/geometry
	@mkdir -p objs/geometry/tesselation
	@mkdir -p objs/geometry/vectors
	@mkdir -p objs/geometry/vectors/vec2
	@mkdir -p objs/geometry/vectors/vec2d
	@mkdir -p objs/geometry/vectors/vec3
	@mkdir -p objs/geometry/vectors/vec3d
	@mkdir -p objs/geometry/vectors/vecu2
	@mkdir -p objs/geometry/vectors/vecu3
	@mkdir -p objs/geometry/map
	@mkdir -p objs/geometry/map/build
	@mkdir -p objs/geometry/map/read
	@mkdir -p objs/geometry/map/style
	@mkdir -p objs/color
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
	@mkdir -p objs/events/keys/handlers/gui
	@mkdir -p objs/events/keys/init
	@mkdir -p objs/events/gui
	@mkdir -p objs/events/init
	@mkdir -p objs/gui
	@mkdir -p objs/gui/controls
	@mkdir -p objs/gui/display/sections
	@mkdir -p objs/gui/panel
	@mkdir -p objs/gui/display/print
	@mkdir -p objs/gui/print
	@mkdir -p objs/gui/style
	@mkdir -p objs/gui/layout

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