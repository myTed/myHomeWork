# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 16:25:58 by kyolee            #+#    #+#              #
#    Updated: 2022/06/15 15:31:12 by kyolee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror -I./include

MANDATORY_DIR=FDF_MANDATORY/
SRCS= main.c map_check.c map_cord.c\
	  draw.c draw_line.c\
	  matrix_parallel.c matrix_parallel_view.c matrix_rol.c matrix_rol_view.c\
	  matrix_operator.c\
	  key_event_handler.c key_event_update.c

BONUS_DIR=FDF_BONUS/
BONUS_SRCS= main_bonus.c\
			map_check_bonus.c map_cord_bonus.c\
			draw_bonus.c draw_line_bonus.c\
			matrix_parallel_bonus.c matrix_parallel_view_bonus.c matrix_rol_bonus.c\
			matrix_rol_view_bonus.c\
			matrix_operator_bonus.c\
			key_event_handler_bonus.c key_event_update_bonus.c

LIB_SRCS=libft/libft.a gnl/libgnl.a

MANDATORY_OBJS=$(addprefix $(MANDATORY_DIR), $(patsubst %.c, %.o, $(SRCS)))
BONUS_OBJS=$(addprefix $(BONUS_DIR), $(patsubst %.c, %.o, $(BONUS_SRCS)))

ifeq ($(BONUS), 1)
	OBJECTS=$(BONUS_OBJS)
else		
	OBJECTS=$(MANDATORY_OBJS)
endif

NAME=fdf

all:$(NAME)

$(NAME):$(OBJECTS) $(LIB_SRCS)
	$(CC) $(CFLAGS) -v -o $@ $^ -L. -lmlx -framework OpenGL -framework AppKit
#$(CC) $(CFLAGS) -o $@ $^ -L../../ -lmlx -lXext -lX11 -lm
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
