# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 16:25:58 by kyolee            #+#    #+#              #
#    Updated: 2022/07/14 18:32:44 by kyolee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror -g
INCLUDES=./include
MANDATORY_DIR=mandatory/
SRCS= main.c arg.c arg_check.c atol.c\
	  op_swap.c op_basic.c op_pop.c op_rotate.c\
	  sort.c sort_partition.c sort_scan.c\
	  sort_transfer_a_to_b.c sort_transfer_b_to_a.c\
	  sort_under_five.c sort_under_three.c\
	  quick_select.c

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
	$(CC) $(CFLAGS)  -v -o $@ $^
#$(CC) $(CFLAGS) -o $@ $^ -L../../ -lmlx -lXext -lX11 -lm
# -fsanitize=address 
$(LIB_SRCS) :
	cd libft && make

%.o:%.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c -o $@ $^

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
