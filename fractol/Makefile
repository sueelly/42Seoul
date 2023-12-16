CC = cc
CLANG = -Wall -Wextra -Werror
NAME = fractol
HEADER = fractol.h
HEADER_BONUS = bonus/fractol_bonus.h
SRCS = etc.c set.c function.c main.c image.c 
SRCS_BONUS = bonus/etc_bonus.c bonus/set_bonus.c bonus/function_bonus.c bonus/main_bonus.c bonus/image_bonus.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CLANG) -lmlx -framework OpenGL -framework Appkit $(OBJS) -o $@ -I $(HEADER)

.c.o: 
	$(CC) $(CLANG) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean:
	make clean
	rm -f $(NAME)

re:
	make fclean
	make all

bonus: $(OBJS_BONUS) $(HEADER_BONUS)
	$(CC) $(CLANG) -lmlx -framework OpenGL -framework Appkit -fsanitize=address $(OBJS_BONUS) -o $(NAME) -I $(HEADER_BONUS)

.PHONY: clean fclean re bonus