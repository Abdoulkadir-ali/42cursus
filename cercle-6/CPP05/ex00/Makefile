NAME        = bureaucrat
CC          = c++
MAKEFLAGS	+= -j4
CFLAGS      = -Wall -Wextra -Werror -g3 -Iincludes -I/includes
RM          = rm -f
SRCS_DIR    = srcs
OBJS_DIR    = objs

SRCS        = $(shell find $(SRCS_DIR) -name "*.cpp")
OBJS        = $(patsubst $(SRCS_DIR)/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test
