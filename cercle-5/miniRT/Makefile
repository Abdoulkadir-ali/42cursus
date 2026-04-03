NAME        = miniRT
MAKEFLAGS	+= j16
MINILIBX_DIR = packages/minilibx-linux
MINILIBX    = $(MINILIBX_DIR)/libmlx.a
LIBFT_DIR   = packages/libft
LIBFT       = $(LIBFT_DIR)/libft.a
LIBS        = -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -lreadline -lm -lz -lXext -lX11 -lpthread



CC          = cc
INCLUDES_DIRS = $(shell find includes -type d)
INCLUDES    = $(addprefix -I,$(INCLUDES_DIRS))
CFLAGS      = -Wall -Wextra -Werror -O3 -march=native -mfma -funroll-loops -ffast-math -flto -g3 -pthread $(INCLUDES) -Ipackages/libft/includes -I$(MINILIBX_DIR) -Ipackages -DDEBUG_EXTENDER -DDEBUG -MMD -MP
RM          = rm -f
SRCS_DIR    = srcs
# Exclude old physics.c if it still exists (handled by file deletion)
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
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@printf "$(GREEN)$(NAME) ready!$(RESET)\n"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\r\033[K$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): FORCE
	@printf "$(YELLOW)Building libft...$(RESET)\n"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MINILIBX):
	@printf "$(YELLOW)Building minilibx...$(RESET)\n"
	@$(MAKE) -s -C $(MINILIBX_DIR)

clean:
	@printf "$(YELLOW)Cleaning objects...$(RESET)\n"
	@$(RM) -r $(OBJS_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@printf "$(YELLOW)Cleaning $(NAME)...$(RESET)\n"
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all


# ── Profiling targets ────────────────────────────────────────────────────────
#
# callgrind (recommended — counts every instruction, sees all threads):
#
#   make profile
#   ./miniRT-prof maps/rt/emissive_test.rt   (run 3-5 seconds, then close)
#   callgrind_annotate --auto=yes callgrind.out.* | head -120
#   OR open it in kcachegrind / qcachegrind if you install one:
#   kcachegrind callgrind.out.*
#
# gprof (fast, single-threaded sampling only — misses pthread workers):
#
#   make gprof-build
#   ./miniRT-gprof maps/rt/emissive_test.rt  (run 5-10 seconds, then close)
#   gprof miniRT-gprof gmon.out | head -80

PROF_OBJS_DIR = objs-prof
PROF_OBJS     = $(patsubst $(SRCS_DIR)/%.c,$(PROF_OBJS_DIR)/%.o,$(SRCS))
PROF_DEPS     = $(PROF_OBJS:.o=.d)

# -O1 keeps the call graph readable; -g3 keeps symbols; no -flto (breaks gprof)
PROF_CFLAGS   = -Wall -Wextra -O1 -g3 -pthread \
                $(INCLUDES) -Ipackages/libft/includes -I$(MINILIBX_DIR) -Ipackages \
                -DDEBUG_EXTENDER -DPROFILE_MESH -DPROFILE_BUILD -DTIME_LOOP -MMD -MP

-include $(PROF_DEPS)

$(PROF_OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(PROF_CFLAGS) -c $< -o $@

# callgrind target — no special compile flags needed; valgrind instruments at run time
profile: $(LIBFT) $(MINILIBX) $(PROF_OBJS)
	$(CC) $(PROF_CFLAGS) $(PROF_OBJS) $(LIBS) -o miniRT-prof
	@echo ""
	@echo "Binary: ./miniRT-prof"
	@echo "Run:    valgrind --tool=callgrind --callgrind-out-file=callgrind.out \\"
	@echo "          --collect-atstart=yes --instr-atstart=yes \\"
	@echo "          ./miniRT-prof maps/rt/emissive_test.rt"
	@echo "Read:   callgrind_annotate --auto=yes callgrind.out | head -120"

# gprof target — needs -pg baked into the binary
GPROF_CFLAGS  = $(PROF_CFLAGS) -pg
GPROF_OBJS_DIR = objs-gprof
GPROF_OBJS     = $(patsubst $(SRCS_DIR)/%.c,$(GPROF_OBJS_DIR)/%.o,$(SRCS))

$(GPROF_OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(GPROF_CFLAGS) -c $< -o $@

gprof-build: $(LIBFT) $(MINILIBX) $(GPROF_OBJS)
	$(CC) $(GPROF_CFLAGS) $(GPROF_OBJS) $(LIBS) -o miniRT-gprof
	@echo ""
	@echo "Binary: ./miniRT-gprof"
	@echo "Run:    ./miniRT-gprof maps/rt/emissive_test.rt  (close after ~5 s)"
	@echo "Read:   gprof miniRT-prof gmon.out | head -80"

prof-clean:
	$(RM) -r $(PROF_OBJS_DIR) $(GPROF_OBJS_DIR) miniRT-prof miniRT-gprof gmon.out callgrind.out*

.PHONY: all clean fclean re test FORCE profile gprof-build prof-clean
