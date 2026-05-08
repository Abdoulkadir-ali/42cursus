NAME        = cub3D
MAKEFLAGS	+= j16
MINILIBX_DIR = packages/minilibx-linux
MINILIBX    = $(MINILIBX_DIR)/libmlx.a
LIBFT_DIR   = packages/libft
LIBFT       = $(LIBFT_DIR)/libft.a
LIBS        = -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -lreadline -lm -lz -lXext -lX11



CC          = gcc
INCLUDES_DIRS = $(shell find includes -type d)
INCLUDES    = $(addprefix -I, $(INCLUDES_DIRS))
CFLAGS      = -Wall -Wextra -Werror -O3 -march=native -mfma -funroll-loops -fPIE \
              -ffast-math -flto=auto -fno-plt -fno-semantic-interposition \
              -fomit-frame-pointer -fvect-cost-model=unlimited -fipa-pta \
              -falign-functions=64 -falign-loops=32 \
              -g3 $(INCLUDES) -Ipackages/libft/includes \
              -I$(MINILIBX_DIR) -Ipackages -DDEBUG_EXTENDER -MMD -MP
MLX_CFLAGS  = -O3 -fPIC
RM          = rm -f
SRCS_DIR    = srcs
OBJS_DIR    = objs
SRCS        = $(shell find $(SRCS_DIR) -name "*.c")
OBJS        = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))



# ── Colors ────────────────────────────────────────────────────────────────────
RESET       = \033[0m
GREEN       = \033[32m
BLUE        = \033[34m
CYAN        = \033[36m
YELLOW      = \033[33m

DEPS        = $(OBJS:.o=.d)

all: $(NAME)

-include $(DEPS)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	@echo ""
	@printf "$(BLUE)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -Wl,-O2 -Wl,--sort-common -o $(NAME)
	@printf "$(GREEN)$(NAME) ready!$(RESET)\n"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(MINILIBX)
	@mkdir -p $(dir $@)
	@printf "\r\033[K$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): FORCE
	@printf "$(YELLOW)Building libft...$(RESET)\n"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MINILIBX):
	@if [ ! -d "$(MINILIBX_DIR)" ]; then \
		printf "$(YELLOW)Cloning minilibx-linux...$(RESET)\n"; \
		git clone --depth=1 https://github.com/42Paris/minilibx-linux.git $(MINILIBX_DIR); \
	fi
	@printf "$(YELLOW)Building minilibx...$(RESET)\n"
	@$(MAKE) -s -C $(MINILIBX_DIR)

clean:
	@printf "$(YELLOW)Cleaning objects...$(RESET)\n"
	@$(RM) -r $(OBJS_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@printf "$(YELLOW)Cleaning $(NAME)...$(RESET)\n"
	@$(RM) $(NAME) Cub3D
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@if [ -f "$(MINILIBX_DIR)/Makefile.gen" ]; then \
		$(MAKE) -s -C $(MINILIBX_DIR) clean; \
	fi

ffclean: fclean
	@printf "$(YELLOW)Cleaning minilibx-linux...$(RESET)\n"
	@$(RM) -r $(MINILIBX_DIR)

re: fclean 
	@$(MAKE) all

bonus: all

FORCE:

.PHONY: all clean fclean ffclean re FORCE