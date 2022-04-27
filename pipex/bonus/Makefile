# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 16:25:58 by kyolee            #+#    #+#              #
#    Updated: 2022/04/28 01:07:10 by kyolee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRCS=ft_pipex.c
BONUS_SRCS=ft_pipex_bonus.c
LIB_SRCS=libft.a

ifeq ($(BONUS), 1)
	OBJECTS=$(patsubst %.c, %.o, $(BONUS_SRCS))
else		
	OBJECTS=$(patsubst %.c, %.o, $(SRCS))
endif

NAME=pipex

all:$(NAME)

$(NAME):$(OBJECTS) $(LIB_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

bonus:
	make BONUS=1

clean:
	rm -rf $(OBJECTS)

fclean:clean
	rm -rf $(NAME)

re:fclean all

.PHONY: clean fclean re bonus
