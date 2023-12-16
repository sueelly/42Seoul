CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = push_swap
BONUS_NAME = checker
HEADER = push_swap.h
BONUS_HEADER = push_swap_bonus.h
SRCS = main.c parsing.c stack.c radix_sort.c etc.c
BONUS_SRCS = main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c parsing.c stack.c etc.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -I $(HEADER) -o $(NAME)

$(BONUS_NAME): $(BONUS_SRCS) $(BONUS_HEADER)
	$(CC) $(CFLAGS) $(BONUS_SRCS) -I $(BONUS_HEADER) -o $(BONUS_NAME)

.c.o : 
	$(CC) $(CFLAGS) -c $< -I $(HEADER) -o $@ 

bonus: $(BONUS_NAME)

clean:
	rm -f $(OBJS)

fclean:
	make clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: clean fclean re bonus