CC = gcc
CLANG = -Wall -Wextra -Werror
NAME = libftprintf.a
HEADER = ft_printf.h
SRCS = ft_printf.c ft_print_arg.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	ar rc $@ $^

.c.o: 
	$(CC) $(CLANG) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	make clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: clean fclean re