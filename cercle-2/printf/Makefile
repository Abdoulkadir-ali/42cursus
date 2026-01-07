NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes

SRC_DIR = srcs
OBJ_DIR = objs
SRC = \
handlers/char.c handlers/percent.c handlers/main.c handlers/nbr.c handlers/ptr.c handlers/str.c handlers/unbr.c  \
handlers/flags/dot.c handlers/flags/hash.c handlers/flags/minus.c handlers/flags/sign.c handlers/flags/width.c handlers/flags/zero.c  \
helpers/ft_atoi.c helpers/ft_isdigit.c helpers/ft_putchar.c helpers/ft_putnbr_base.c helpers/ft_putnchar.c helpers/ft_putnstr.c helpers/ft_putstr.c helpers/ft_strchr.c helpers/ft_strlen.c  \
parsers/length.c parsers/main.c parsers/precision.c parsers/width.c  \
printf/ft_printf.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/ft_printf.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all
	@echo "Bonus: Running printfTester"
	@if [ -d printfTester ]; then \
		cd printfTester && make && ./test; \
	else \
		echo "printfTester not found"; \
	fi

norm:
	norminette srcs includes

main: $(NAME) srcs/main/main.o
	gcc srcs/main/main.o -L. -lftprintf -o main

srcs/main/main.o: srcs/main/main.c includes/ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re main bonus norm
