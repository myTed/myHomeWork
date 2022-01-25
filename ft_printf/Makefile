# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 14:27:47 by kyolee            #+#    #+#              #
#    Updated: 2022/01/25 14:34:43 by kyolee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRCS=ft_printf.c

OBJECTS=$(patsubst %.c, %.o, $(SRCS))

all:$(NAME)

$(NAME):$(OBJECTS)
	ar rcs $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf *.o

fclean:clean
	rm -rf $(NAME)

re:fclean all

.PHONY: clean fclean all re


