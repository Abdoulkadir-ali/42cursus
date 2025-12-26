NAME = fdf

CC = clang
CFLAGS = -Wall -Wextra -Werror -I. -I./includes -I./minilibx-linux -I./libft/includes -O3 -ffast-math
LDFLAGS = -L./minilibx-linux -lmlx -L./libft -lft -lX11 -lXext -lm -lpthread

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

#SRCS = $(shell find srcs -name "*.c" | sort) if you want to go faster, but it can be dangerous

SRCS =	srcs/core/cleanup.c \
		srcs/core/init.c \
		srcs/core/main.c \
		srcs/events/gui/fps.c \
		srcs/events/gui/resize.c \
		srcs/events/init/hooks.c \
		srcs/events/init/init.c \
		srcs/events/init/keys.c \
		srcs/events/init/loop.c \
		srcs/events/init/mouse.c \
		srcs/events/keys/handlers/combos/combo.c \
		srcs/events/keys/handlers/combos/helper.c \
		srcs/events/keys/handlers/flags/flag.c \
		srcs/events/keys/handlers/flags/helper.c \
		srcs/events/keys/handlers/flags/modifiers.c \
		srcs/events/keys/handlers/gui/leave.c \
		srcs/events/keys/handlers/map/map.c \
		srcs/events/keys/handlers/map/color_mode.c \
		srcs/events/keys/handlers/toggle/camera.c \
		srcs/events/keys/handlers/toggle/optimizations.c \
		srcs/events/keys/handlers/toggle/tesselation/bracket.c \
		srcs/events/keys/handlers/toggle/tesselation/level.c \
		srcs/events/keys/handlers/toggle/tesselation/lod.c \
		srcs/events/keys/handlers/toggle/tesselation/points.c \
		srcs/events/keys/handlers/toggle/tesselation/toggle.c \
		srcs/events/keys/handlers/view/align.c \
		srcs/events/keys/handlers/view/camera.c \
		srcs/events/keys/handlers/view/helper.c \
		srcs/events/keys/handlers/view/rotation.c \
		srcs/events/keys/init/init.c \
		srcs/events/keys/init/keys/actions.c \
		srcs/events/keys/init/keys/keys.c \
		srcs/events/keys/init/keys/releases.c \
		srcs/events/mouse/handlers.c \
		srcs/events/mouse/move.c \
		srcs/events/mouse/press.c \
		srcs/geometry/color/create.c \
		srcs/geometry/color/get.c \
		srcs/geometry/color/transform.c \
		srcs/geometry/map/build/grid.c \
		srcs/geometry/map/build/helper.c \
		srcs/geometry/map/build/minmax.c \
		srcs/geometry/map/read/file.c \
		srcs/geometry/map/read/helper.c \
		srcs/geometry/map/read/loader.c \
		srcs/geometry/map/read/parser.c \
		srcs/geometry/map/read/select.c \
		srcs/geometry/map/style/style.c \
		srcs/geometry/map/style/themes.c \
		srcs/geometry/tesselation/compute.c \
		srcs/geometry/tesselation/diagonal.c \
		srcs/geometry/tesselation/direct.c \
		srcs/geometry/tesselation/helper.c \
		srcs/geometry/tesselation/horizontal.c \
		srcs/geometry/tesselation/manager.c \
		srcs/geometry/tesselation/submap.c \
		srcs/geometry/tesselation/tesselation.c \
		srcs/geometry/tesselation/utils.c \
		srcs/geometry/tesselation/vertical.c \
		srcs/graphics/cache/cache.c \
		srcs/graphics/cache/helper.c \
		srcs/graphics/draw/grid/quad/quad.c \
		srcs/graphics/draw/grid/raycast/grid.c \
		srcs/graphics/draw/grid/raycast/helper.c \
		srcs/graphics/draw/grid/raycast/primitive.c \
		srcs/graphics/draw/grid/raycast/raycast.c \
		srcs/graphics/draw/grid/raycast/threads.c \
		srcs/graphics/draw/grid/raycast/utils.c \
		srcs/graphics/draw/grid/segment/segment.c \
		srcs/graphics/draw/grid/segment/tessellation.c \
		srcs/graphics/draw/grid/segment/utils.c \
		srcs/graphics/draw/grid/threads.c \
		srcs/graphics/draw/lines/bresenham/bresenham.c \
		srcs/graphics/draw/lines/bresenham/helper.c \
		srcs/graphics/draw/lines/bresenham/raycast.c \
		srcs/graphics/draw/lines/bresenham/standard.c \
		srcs/graphics/draw/lines/draw/draw.c \
		srcs/graphics/draw/lines/draw/line_setup.c \
		srcs/graphics/draw/lines/helper.c \
		srcs/graphics/draw/pixel/pixel.c \
		srcs/graphics/frames/clear.c \
		srcs/graphics/init/init.c \
		srcs/gui/gui/init.c \
		srcs/gui/gui/redraw.c \
		srcs/gui/layout/axis/drawing.c \
		srcs/gui/layout/axis/indicator.c \
		srcs/gui/layout/axis/labels.c \
		srcs/gui/layout/layout.c \
		srcs/gui/layout/map/map.c \
		srcs/gui/layout/performance/algorithm.c \
		srcs/gui/layout/performance/optimizations.c \
		srcs/gui/layout/performance/performance.c \
		srcs/gui/layout/performance/points.c \
		srcs/gui/layout/performance/projection.c \
		srcs/gui/layout/performance/tesselation.c \
		srcs/gui/layout/style.c \
		srcs/gui/layout/titles/draw.c \
		srcs/gui/layout/titles/section.c \
		srcs/gui/layout/titles/helper.c \
		srcs/gui/layout/transform/fps.c \
		srcs/gui/layout/transform/movement.c \
		srcs/gui/layout/transform/pos.c \
		srcs/gui/layout/transform/rot.c \
		srcs/gui/layout/transform/scale.c \
		srcs/gui/layout/transform/transform.c \
		srcs/gui/layout/transform/utils.c \
		srcs/gui/panel/clear.c \
		srcs/gui/panel/draw.c \
		srcs/gui/panel/redraw.c \
		srcs/gui/print/format/format.c \
		srcs/gui/print/format/nbr.c \
		srcs/gui/print/put.c \
		srcs/gui/theme/theme.c \
		srcs/gui/theme/utils.c \
		srcs/primitives/clamp.c \
		srcs/primitives/vectors/vec2/arithmetic.c \
		srcs/primitives/vectors/vec2/distance.c \
		srcs/primitives/vectors/vec2/init.c \
		srcs/primitives/vectors/vec2d/arithmetic.c \
		srcs/primitives/vectors/vec2d/distance.c \
		srcs/primitives/vectors/vec2d/init.c \
		srcs/primitives/vectors/vec3/arithmetic.c \
		srcs/primitives/vectors/vec3/distance.c \
		srcs/primitives/vectors/vec3/init.c \
		srcs/primitives/vectors/vec3d/arithmetic.c \
		srcs/primitives/vectors/vec3d/distance.c \
		srcs/primitives/vectors/vec3d/init.c \
		srcs/primitives/vectors/vecu2/arithmetic.c \
		srcs/primitives/vectors/vecu2/distance.c \
		srcs/primitives/vectors/vecu2/init.c \
		srcs/primitives/vectors/vecu3/arithmetic.c \
		srcs/primitives/vectors/vecu3/distance.c \
		srcs/primitives/vectors/vecu3/init.c \
		srcs/primitives/matrix/matrix.c \
		srcs/render/camera/controls/adjust.c \
		srcs/render/camera/controls/center.c \
		srcs/render/camera/controls/reset_style.c \
		srcs/render/camera/controls/rotate/build.c \
		srcs/render/camera/controls/rotate/init.c \
		srcs/render/camera/controls/rotate/multiply.c \
		srcs/render/camera/controls/rotate/rotate.c \
		srcs/render/camera/controls/zoom.c \
		srcs/render/camera/init.c \
		srcs/render/camera/map_init.c \
		srcs/render/optimization/lines.c \
		srcs/render/stages/culling/bounds.c \
		srcs/render/stages/culling/culling.c \
		srcs/render/stages/culling/visibility.c \
		srcs/render/stages/pipeline/adaptive.c \
		srcs/render/stages/pipeline/geometry.c \
		srcs/render/stages/pipeline/lod.c \
		srcs/render/stages/pipeline/rasterization.c \
		srcs/render/stages/pipeline/render.c \
		srcs/render/stages/pipeline/tesselation.c \
		srcs/render/stages/projections/matrix.c \
		srcs/render/stages/projections/scanlines/scanline.c \
		srcs/render/stages/projections/transform.c \
		srcs/render/stages/projections/view.c  \
		srcs/window/init.c
	


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

.PHONY: all clean fclean re objs