NAME        = sed_is_for_losers
CC          = c++
MAKEFLAGS	+= -j4
CFLAGS      = -Wall -Wextra -Werror -g3 -Iincludes -std=c++98
RM          = rm -f
OBJS_DIR    = objs

SRCS        = main.cpp srcs/Sed.cpp
OBJS        = $(patsubst %.cpp,$(OBJS_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
