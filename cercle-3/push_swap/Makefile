NAME = push_swap

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes -I srcs/libft/includes

LIBFT_DIR = srcs/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = srcs/push_swap
SRC = $(SRC_DIR)/parsing/stacks/check.c \
      $(SRC_DIR)/parsing/stacks/parser.c \
      $(SRC_DIR)/parsing/stacks/test.c \
      $(SRC_DIR)/parsing/stacks/main.c \
      $(SRC_DIR)/main/main.c \
	  $(SRC_DIR)/parsing/moves/parser.c \
      $(SRC_DIR)/moves/push.c \
      $(SRC_DIR)/moves/rotate.c \
	  $(SRC_DIR)/moves/reverse_rotate.c \
      $(SRC_DIR)/moves/swap.c \
      $(SRC_DIR)/moves/test.c \
      $(SRC_DIR)/helper/display/ft_print_lst.c \
      $(SRC_DIR)/helper/display/ft_puterr.c \
      $(SRC_DIR)/parsing/stacks/parse_int.c \
      $(SRC_DIR)/helper/lst/ft_new.c \
      $(SRC_DIR)/helper/lst/ft_add_back.c \
      $(SRC_DIR)/helper/lst/ft_add_front.c \
      $(SRC_DIR)/helper/lst/ft_size.c \
      $(SRC_DIR)/helper/lst/ft_last.c \
      $(SRC_DIR)/helper/lst/ft_delone.c \
      $(SRC_DIR)/helper/lst/ft_clear.c \
      $(SRC_DIR)/helper/stacks/free.c \
      $(SRC_DIR)/algo/cost.c \
      $(SRC_DIR)/algo/target.c \
      $(SRC_DIR)/algo/moves.c \
      $(SRC_DIR)/algo/sort.c \
      $(SRC_DIR)/algo/push_swap.c \
      $(SRC_DIR)/checker/checker.c \

OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST_OBJ = $(OBJ_DIR)/parsing/stacks/check.o \
			$(OBJ_DIR)/parsing/stacks/parser.o \
			$(OBJ_DIR)/parsing/stacks/test.o \
			$(OBJ_DIR)/helper/lst/ft_new.o \
			$(OBJ_DIR)/helper/lst/ft_add_back.o \
			$(OBJ_DIR)/helper/lst/ft_add_front.o \
			$(OBJ_DIR)/helper/lst/ft_clear.o \
			$(OBJ_DIR)/helper/stacks/free.o \
			$(OBJ_DIR)/helper/lst/ft_delone.o \
			$(OBJ_DIR)/helper/lst/ft_size.o \
			$(OBJ_DIR)/helper/lst/ft_last.o \
			$(OBJ_DIR)/helper/display/ft_puterr.o \
			$(OBJ_DIR)/parsing/stacks/parse_int.o

MOVES_TEST_OBJ = $(OBJ_DIR)/parsing/stacks/check.o \
				 $(OBJ_DIR)/parsing/stacks/parser.o \
				 $(OBJ_DIR)/moves/test.o \
				 $(OBJ_DIR)/parsing/moves/parser.o \
				 $(OBJ_DIR)/moves/push.o \
				 $(OBJ_DIR)/moves/rotate.o \
				 $(OBJ_DIR)/moves/reverse_rotate.o \
				 $(OBJ_DIR)/moves/swap.o \
				 $(OBJ_DIR)/helper/lst/ft_new.o \
				 $(OBJ_DIR)/helper/lst/ft_add_back.o \
				 $(OBJ_DIR)/helper/lst/ft_add_front.o \
				 $(OBJ_DIR)/helper/lst/ft_clear.o \
				 $(OBJ_DIR)/helper/stacks/free.o \
				 $(OBJ_DIR)/helper/lst/ft_delone.o \
				 $(OBJ_DIR)/helper/lst/ft_size.o \
				 $(OBJ_DIR)/helper/lst/ft_last.o \
				 $(OBJ_DIR)/helper/display/ft_print_lst.o \
				 $(OBJ_DIR)/helper/display/ft_puterr.o \
				 $(OBJ_DIR)/algo/sort.o \
				 $(OBJ_DIR)/algo/cost.o \
				 $(OBJ_DIR)/algo/target.o \
				 $(OBJ_DIR)/algo/moves.o \
				 $(OBJ_DIR)/parsing/stacks/parse_int.o

ALGO_TEST_OBJ = $(OBJ_DIR)/parsing/stacks/check.o \
				$(OBJ_DIR)/parsing/stacks/parser.o \
				$(OBJ_DIR)/algo/tests/main.o \
				$(OBJ_DIR)/parsing/moves/parser.o \
				$(OBJ_DIR)/moves/push.o \
				$(OBJ_DIR)/moves/rotate.o \
				$(OBJ_DIR)/moves/reverse_rotate.o \
				$(OBJ_DIR)/moves/swap.o \
				$(OBJ_DIR)/helper/lst/ft_new.o \
				$(OBJ_DIR)/helper/lst/ft_add_back.o \
				$(OBJ_DIR)/helper/lst/ft_add_front.o \
				$(OBJ_DIR)/helper/lst/ft_clear.o \
				$(OBJ_DIR)/helper/stacks/free.o \
				$(OBJ_DIR)/helper/lst/ft_delone.o \
				$(OBJ_DIR)/helper/lst/ft_size.o \
				$(OBJ_DIR)/helper/lst/ft_last.o \
				$(OBJ_DIR)/helper/display/ft_print_lst.o \
				$(OBJ_DIR)/helper/display/ft_puterr.o \
				$(OBJ_DIR)/algo/sort.o \
				$(OBJ_DIR)/algo/cost.o \
				$(OBJ_DIR)/algo/target.o \
				$(OBJ_DIR)/algo/moves.o \
				$(OBJ_DIR)/algo/push_swap.o \
				$(OBJ_DIR)/parsing/stacks/parse_int.o

COST_TEST_OBJ = $(OBJ_DIR)/parsing/stacks/check.o \
				$(OBJ_DIR)/parsing/stacks/parser.o \
				$(OBJ_DIR)/algo/tests/cost.o \
				$(OBJ_DIR)/parsing/moves/parser.o \
				$(OBJ_DIR)/moves/push.o \
				$(OBJ_DIR)/moves/rotate.o \
				$(OBJ_DIR)/moves/reverse_rotate.o \
				$(OBJ_DIR)/moves/swap.o \
				$(OBJ_DIR)/helper/lst/ft_new.o \
				$(OBJ_DIR)/helper/lst/ft_add_back.o \
				$(OBJ_DIR)/helper/lst/ft_add_front.o \
				$(OBJ_DIR)/helper/lst/ft_clear.o \
				$(OBJ_DIR)/helper/stacks/free.o \
				$(OBJ_DIR)/helper/lst/ft_delone.o \
				$(OBJ_DIR)/helper/lst/ft_size.o \
				$(OBJ_DIR)/helper/lst/ft_last.o \
				$(OBJ_DIR)/helper/display/ft_print_lst.o \
				$(OBJ_DIR)/helper/display/ft_puterr.o \
				$(OBJ_DIR)/algo/sort.o \
				$(OBJ_DIR)/algo/cost.o \
				$(OBJ_DIR)/algo/target.o \
				$(OBJ_DIR)/algo/moves.o \
				$(OBJ_DIR)/algo/push_swap.o \
				$(OBJ_DIR)/parsing/stacks/parse_int.o

TARGET_TEST_OBJ = $(OBJ_DIR)/parsing/stacks/check.o \
				$(OBJ_DIR)/parsing/stacks/parser.o \
				$(OBJ_DIR)/algo/tests/target.o \
				$(OBJ_DIR)/parsing/moves/parser.o \
				$(OBJ_DIR)/moves/push.o \
				$(OBJ_DIR)/moves/rotate.o \
				$(OBJ_DIR)/moves/reverse_rotate.o \
				$(OBJ_DIR)/moves/swap.o \
				$(OBJ_DIR)/helper/lst/ft_new.o \
				$(OBJ_DIR)/helper/lst/ft_add_back.o \
				$(OBJ_DIR)/helper/lst/ft_add_front.o \
				$(OBJ_DIR)/helper/lst/ft_clear.o \
				$(OBJ_DIR)/helper/stacks/free.o \
				$(OBJ_DIR)/helper/lst/ft_delone.o \
				$(OBJ_DIR)/helper/lst/ft_size.o \
				$(OBJ_DIR)/helper/lst/ft_last.o \
				$(OBJ_DIR)/helper/display/ft_print_lst.o \
				$(OBJ_DIR)/helper/display/ft_puterr.o \
				$(OBJ_DIR)/algo/sort.o \
				$(OBJ_DIR)/algo/cost.o \
				$(OBJ_DIR)/algo/target.o \
				$(OBJ_DIR)/algo/moves.o \
				$(OBJ_DIR)/algo/push_swap.o \
				$(OBJ_DIR)/parsing/stacks/parse_int.o

CHECKER_OBJ = $(OBJ_DIR)/parsing/stacks/check.o \
				 $(OBJ_DIR)/parsing/stacks/parser.o \
				 $(OBJ_DIR)/checker/checker.o \
				 $(OBJ_DIR)/parsing/moves/parser.o \
				 $(OBJ_DIR)/moves/push.o \
				 $(OBJ_DIR)/moves/rotate.o \
				 $(OBJ_DIR)/moves/reverse_rotate.o \
				 $(OBJ_DIR)/moves/swap.o \
				 $(OBJ_DIR)/helper/lst/ft_new.o \
				 $(OBJ_DIR)/helper/lst/ft_add_back.o \
				 $(OBJ_DIR)/helper/lst/ft_add_front.o \
				 $(OBJ_DIR)/helper/lst/ft_clear.o \
				 $(OBJ_DIR)/helper/stacks/free.o \
				 $(OBJ_DIR)/helper/lst/ft_delone.o \
				 $(OBJ_DIR)/helper/lst/ft_size.o \
				 $(OBJ_DIR)/helper/lst/ft_last.o \
				 $(OBJ_DIR)/helper/display/ft_print_lst.o \
				 $(OBJ_DIR)/helper/display/ft_puterr.o \
				 $(OBJ_DIR)/algo/sort.o \
				 $(OBJ_DIR)/algo/cost.o \
				 $(OBJ_DIR)/algo/target.o \
				 $(OBJ_DIR)/algo/moves.o \
				 $(OBJ_DIR)/parsing/stacks/parse_int.o


BONUS_SRC = $(SRC_DIR)/checker/checker.c \
			$(SRC_DIR)/checker/parser.c \



all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(filter-out $(OBJ_DIR)/parsing/stacks/test.o $(OBJ_DIR)/moves/test.o $(OBJ_DIR)/checker/checker.o $(OBJ_DIR)/parsing/moves/parser.o $(OBJ_DIR)/checker/test.o, $(OBJ)) $(LIBFT)
	$(CC) $(CFLAGS) $(filter-out $(OBJ_DIR)/parsing/stacks/test.o $(OBJ_DIR)/moves/test.o $(OBJ_DIR)/parsing/stacks/main.o $(OBJ_DIR)/checker/checker.o $(OBJ_DIR)/parsing/moves/parser.o $(OBJ_DIR)/checker/test.o, $(OBJ)) $(LIBFT) -o $(NAME)

checker: $(filter-out $(OBJ_DIR)/parsing/stacks/test.o $(OBJ_DIR)/moves/test.o $(OBJ_DIR)/main/main.o $(OBJ_DIR)/parsing/stacks/main.o, $(OBJ)) $(LIBFT)
	$(CC) $(CFLAGS) $(filter-out $(OBJ_DIR)/parsing/stacks/test.o $(OBJ_DIR)/moves/test.o $(OBJ_DIR)/main/main.o $(OBJ_DIR)/parsing/stacks/main.o $(OBJ_DIR)/checker/checker.o $(OBJ_DIR)/parsing/moves/parser.o $(OBJ_DIR)/checker/test.o, $(OBJ)) obj/checker/checker.o obj/parsing/moves/parser.o $(LIBFT) -o checker

test: tests/parser tests/move tests/algo tests/cost tests/target

tests/parser: $(TEST_OBJ) $(LIBFT)
	@mkdir -p tests
	$(CC) $(CFLAGS) $(TEST_OBJ) $(LIBFT) -o tests/parser

tests/move: $(MOVES_TEST_OBJ) $(LIBFT)
	@mkdir -p tests
	$(CC) $(CFLAGS) $(MOVES_TEST_OBJ) $(LIBFT) -o tests/move

tests/algo: $(ALGO_TEST_OBJ) $(LIBFT)
	@mkdir -p tests
	$(CC) $(CFLAGS) $(ALGO_TEST_OBJ) $(LIBFT) -o tests/algo

tests/cost: $(COST_TEST_OBJ) $(LIBFT)
	@mkdir -p tests
	$(CC) $(CFLAGS) $(COST_TEST_OBJ) $(LIBFT) -o tests/cost

tests/target: $(TARGET_TEST_OBJ) $(LIBFT)
	@mkdir -p tests
	$(CC) $(CFLAGS) $(TARGET_TEST_OBJ) $(LIBFT) -o tests/target

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) checker tests/parser tests/move tests/algo tests/cost tests/target
	make fclean -C $(LIBFT_DIR)

re: fclean all

bonus: checker

.PHONY: all clean fclean re test checker bonus
