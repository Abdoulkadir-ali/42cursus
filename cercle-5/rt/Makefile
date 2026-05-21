# **************************************************************************** #
#                              miniRT Makefile                                 #
# **************************************************************************** #

NAME        := miniRT

CC          := cc
PKG_DIR     := packages
MLX_DIR     := $(PKG_DIR)/minilibx-linux
STB_DIR     := $(PKG_DIR)/stb_image
LIBFT_DIR   := $(PKG_DIR)/libft
LIBFT       := $(LIBFT_DIR)/libft.a

SRC_DIR     := src
OBJ_DIR     := objs
INCLUDES_DIR := include
INCLUDES    := $(shell find $(INCLUDES_DIR) -type f -name "*.h")
INC_DIRS    := $(sort $(dir $(INCLUDES)))

CFLAGS      := -Wall -Wextra -Werror -O3 -ffast-math -funroll-loops \
               -fno-math-errno -fomit-frame-pointer -DNDEBUG
CFLAGS      += -march=native -mtune=native
CFLAGS      += -iquote $(INCLUDES_DIR) $(addprefix -I,$(INC_DIRS))
CFLAGS      += -I$(PKG_DIR) -I$(MLX_DIR) -I$(STB_DIR) -I$(LIBFT_DIR)/includes
LDFLAGS     := -L$(MLX_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lpthread
MAKEFLAGS   := --no-print-directory -j$(shell nproc)

SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

MLX_LIB     := $(MLX_DIR)/libmlx_Linux.a
STB_HDR         := $(STB_DIR)/stb_image.h
STB_WRITE_HDR   := $(STB_DIR)/stb_image_write.h
MLX_REPO        := https://github.com/42Paris/minilibx-linux.git
STB_URL         := https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
STB_WRITE_URL   := https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h

all: $(MLX_LIB) $(STB_HDR) $(STB_WRITE_HDR) $(NAME)

$(MLX_DIR):
	@echo "Cloning MiniLibX into $@"
	@mkdir -p $(PKG_DIR)
	@git clone --depth 1 $(MLX_REPO) $@ >/dev/null 2>&1

$(MLX_LIB): | $(MLX_DIR)
	@echo "Building MiniLibX"
	@$(MAKE) -C $(MLX_DIR) >/dev/null 2>&1 || true

$(STB_HDR):
	@echo "Fetching stb_image.h into $@"
	@mkdir -p $(STB_DIR)
	@(command -v curl >/dev/null && curl -fsSL $(STB_URL) -o $@) \
		|| (command -v wget >/dev/null && wget -q $(STB_URL) -O $@) \
		|| (echo "Error: need curl or wget to fetch stb_image.h" && exit 1)

$(STB_WRITE_HDR):
	@echo "Fetching stb_image_write.h into $@"
	@mkdir -p $(STB_DIR)
	@(command -v curl >/dev/null && curl -fsSL $(STB_WRITE_URL) -o $@) \
		|| (command -v wget >/dev/null && wget -q $(STB_WRITE_URL) -O $@) \
		|| (echo "Error: need curl or wget to fetch stb_image_write.h" && exit 1)

$(LIBFT):
	@echo "Building libft"
	@$(MAKE) -C $(LIBFT_DIR) >/dev/null 2>&1

$(NAME): $(OBJS) $(LIBFT)
	@echo "Linking $@"
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(STB_HDR) $(MLX_DIR)
	@mkdir -p $(dir $@)
	@echo "CC  $<"
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# stb_image: third-party single-header — silence warnings for its impl TU.
$(OBJ_DIR)/utils/stb_image_impl.o: $(SRC_DIR)/utils/stb_image_impl.c | $(STB_HDR)
	@mkdir -p $(dir $@)
	@echo "CC  $< (stb)"
	@$(CC) -O3 -ffast-math -I$(STB_DIR) -w -c $< -o $@

$(OBJ_DIR)/utils/stb_image_write_impl.o: $(SRC_DIR)/utils/stb_image_write_impl.c | $(STB_WRITE_HDR)
	@mkdir -p $(dir $@)
	@echo "CC  $< (stb_write)"
	@$(CC) -O3 -ffast-math -I$(STB_DIR) -w -c $< -o $@

-include $(DEPS)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

ffclean: fclean
	@echo "Removing third-party packages"
	@rm -rf $(MLX_DIR) $(STB_DIR)

re: fclean 
	$(MAKE) all

.PHONY: all clean fclean ffclean re
