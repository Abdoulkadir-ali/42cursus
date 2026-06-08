NAME     = RPN
CC       = c++
CFLAGS   = -Wall -Wextra -Werror -std=c++98
RM       = rm -f
OBJS_DIR = objs

SRCS     = main.cpp RPN.cpp
OBJS     = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: %.cpp RPN.hpp
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
