
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = srcs/core/main.c \
       srcs/core/parse.c \
	   srcs/lib/ft_atoi.c \
	   srcs/core/ft_putnbr_base.c \
       srcs/helper/print.c \
       srcs/helper/time.c \
       srcs/routine/death.c \
       srcs/routine/eat.c \
       srcs/routine/routine.c \
       srcs/routine/sleep.c \
       srcs/routine/helper.c

OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

# Colors
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) ready!$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning objects...$(RESET)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
