CC = cc
CFLAGS = -fsanitize=thread -Wall -Wextra -Werror
SRC = main.c init.c free.c etc.c eating_philosophers.c print.c
OBJ = $(SRC:.c=.o)
NAME = philo

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)
	
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
clean:
	rm -f $(OBJ)

fclean: 
	make clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re 