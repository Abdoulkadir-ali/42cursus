NAME        = zombiehorde
CC          = c++
MAKEFLAGS	+= -j4
CFLAGS      = -Wall -Wextra -Werror -g3 -std=c++98
RM          = rm -f
OBJS_DIR    = objs

SRCS        = $(shell find . -name "*.cpp")
OBJS        = $(patsubst ./%.cpp,$(OBJS_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: ./%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test
