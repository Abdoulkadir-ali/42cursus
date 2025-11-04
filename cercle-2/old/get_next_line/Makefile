# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
BUFFER_FLAG = -D BUFFER_SIZE=42

# Directories
OBJ_DIR = obj

# Project name
NAME = $(OBJ_DIR)/get_next_line.a
EXEC = gnl

# Source files
SRCS = get_next_line.c get_next_line_utils.c
SRCS_BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c

# Object files
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))
MAIN_OBJ = $(OBJ_DIR)/main.o

# Default target
all: $(NAME) $(EXEC)

# Build the library
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Build the executable with main
$(EXEC): $(MAIN_OBJ) $(NAME)
	$(CC) $(CFLAGS) $(BUFFER_FLAG) $(MAIN_OBJ) $(NAME) -o $(EXEC)

# Compile .c files to .o files in obj directory
$(OBJ_DIR)/%.o: %.c get_next_line.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(BUFFER_FLAG) -c $< -o $@

$(OBJ_DIR)/%_bonus.o: %_bonus.c get_next_line_bonus.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(BUFFER_FLAG) -c $< -o $@

# Bonus target
bonus: $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS)

# Create obj directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean object files and library
fclean: clean

# Rebuild everything
re: fclean all

# Run the program
run: $(EXEC)
	./$(EXEC)

# Phony targets
.PHONY: all clean fclean re run bonus