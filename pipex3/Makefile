# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 16:25:58 by kyolee            #+#    #+#              #
#    Updated: 2022/04/28 20:30:05 by kyolee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror

SRCS=ft_pipex_main.c	ft_pipex_utils_gnl.c 	ft_pipex_utils_gnl_utils.c\
	 ft_pipex_arg.c		ft_pipex_cmd.c 			ft_pipex_file.c\
	 ft_pipex_fd.c		ft_pipex_exec.c

BONUS_SRCS=ft_pipex_main_bonus.c	ft_pipex_utils_gnl_bonus.c 	ft_pipex_utils_gnl_utils_bonus.c\
		   ft_pipex_arg_bonus.c		ft_pipex_cmd_bonus.c 		ft_pipex_file_bonus.c\
		   ft_pipex_fd_bonus.c		ft_pipex_exec_bonus.c

LIB_SRCS=./libft/libft.a
MANDATORY_OBJS=$(patsubst %.c, %.o, $(SRCS))
BONUS_OBJS=$(patsubst %.c, %.o, $(BONUS_SRCS))


ifeq ($(BONUS), 1)
	OBJECTS=$(BONUS_OBJS)
else		
	OBJECTS=$(MANDATORY_OBJS)
endif

NAME=pipex

all:$(NAME)

$(NAME):$(OBJECTS) $(LIB_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

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
