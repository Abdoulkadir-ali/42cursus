CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f
AR = ar rcs
NAME = libgnl.a
OBJDIR = objs

# Mandatory files
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

# Bonus files
BONUS_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c
BONUS_OBJS = $(addprefix $(OBJDIR)/, $(BONUS_SRCS:.c=.o))

ifdef BUFFER_SIZE
CFLAGS += -DBUFFER_SIZE=$(BUFFER_SIZE)
endif

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	$(AR) $@ $(OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(OBJDIR) $(BONUS_OBJS)
	$(AR) $(NAME) $(BONUS_OBJS)

.PHONY: all clean fclean re bonus