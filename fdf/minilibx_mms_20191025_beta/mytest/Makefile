# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 16:25:58 by kyolee            #+#    #+#              #
#    Updated: 2022/06/11 02:01:42 by kyolee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror -g

SRCS= main.c map.c matrix.c

#BONUS_SRCS=ft_pipex_main_bonus.c	ft_pipex_utils_gnl_bonus.c 	ft_pipex_utils_gnl_utils_bonus.c\
		   ft_pipex_arg_bonus.c		ft_pipex_cmd_bonus.c 		ft_pipex_file_bonus.c\
		   ft_pipex_fd_bonus.c		ft_pipex_exec_bonus.c

LIB_SRCS=./libft/libft.a ./gnl/libgnl.a

MANDATORY_OBJS=$(patsubst %.c, %.o, $(SRCS))
#BONUS_OBJS=$(patsubst %.c, %.o, $(BONUS_SRCS))


ifeq ($(BONUS), 1)
	OBJECTS=$(BONUS_OBJS)
else		
	OBJECTS=$(MANDATORY_OBJS)
endif

NAME=fdf

all:$(NAME)

$(NAME):$(OBJECTS) $(LIB_SRCS)
#$(CC) $(CFLAGS) -v -o $@ $^ -L. -lmlx -framework OpenGL -framework AppKit
	$(CC) $(CFLAGS) -v -o $@ $^ -L.. -lmlx -lXext -lX11 -lm
# -fsanitize=address 
$(LIB_SRCS) :
	cd libft && make
	cd gnl && make

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

bonus:
	make BONUS=1

clean:
	cd libft && make clean
	cd gnl && make clean
	rm -rf $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean:clean
	cd libft && make fclean
	cd gnl && make fclean
	rm -rf $(NAME)

re:fclean all

.PHONY: clean fclean re bonus
