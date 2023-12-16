# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/04 17:19:20 by jchoi2            #+#    #+#              #
#    Updated: 2023/10/20 02:24:26 by haejokim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CLANG = -Wall -Wextra -Werror
CLIENT = client
SERVER = server
NAME = $(CLIENT) $(SERVER)
HEADER = minitalk.h
HEADER_BONUS = minitalk_bonus.h
SRCS_CLIENT = client.c etc.c
SRCS_SERVER = server.c etc.c
SRCS_CLIENT_BONUS = client_bonus.c etc.c
SRCS_SERVER_BONUS = server_bonus.c etc.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)
OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)

all: $(NAME)

$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(CLANG) $(OBJS_CLIENT) -I $(HEADER) -o $@

$(SERVER): $(OBJS_SERVER)
	$(CC) $(CLANG) $(OBJS_SERVER) -I $(HEADER) -o $@

bonus: $(SRCS_CLIENT_BONUS) $(SRCS_SERVER_BONUS)
	$(CC) $(CLANG) $(SRCS_CLIENT_BONUS) -I $(HEADER_BONUS) -o client
	$(CC) $(CLANG) $(SRCS_SERVER_BONUS) -I $(HEADER_BONUS) -o server
	touch bonus

.c.o: $(HEADER)
	$(CC) $(CLANG) -c $< -o $@

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_CLIENT_BONUS)
	rm -f $(OBJS_SERVER) $(OBJS_SERVER_BONUS)

fclean:
	make clean
	rm -f $(NAME) 

re: 
	$(MAKE) fclean
	$(MAKE) all

.PHONY: re fclean clean