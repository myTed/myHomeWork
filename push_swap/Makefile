# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 16:25:58 by kyolee            #+#    #+#              #
#    Updated: 2022/07/11 22:15:29 by kyolee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror -g -I./include

MANDATORY_DIR=mandatory/
SRCS= push_main.c push_operation.c push_sort.c push_arg.c\
	  push_atol.c

BONUS_DIR=bonus/
BONUS_SRCS= main_bonus.c\

LIB_SRCS=libft/libft.a

MANDATORY_OBJS=$(addprefix $(MANDATORY_DIR), $(patsubst %.c, %.o, $(SRCS)))
BONUS_OBJS=$(addprefix $(BONUS_DIR), $(patsubst %.c, %.o, $(BONUS_SRCS)))

ifeq ($(BONUS), 1)
	OBJECTS=$(BONUS_OBJS)
else		
	OBJECTS=$(MANDATORY_OBJS)
endif

NAME=push_swap

all:$(NAME)

$(NAME):$(OBJECTS) $(LIB_SRCS)
	$(CC) $(CFLAGS) -v -o $@ $^
#$(CC) $(CFLAGS) -o $@ $^ -L../../ -lmlx -lXext -lX11 -lm
# -fsanitize=address 
$(LIB_SRCS) :
	cd libft && make

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

bonus:
	make BONUS=1

clean:
	cd libft && make clean
	rm -rf $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean:clean
	cd libft && make fclean
	rm -rf $(NAME)

re:fclean all

.PHONY: clean fclean re bonus
