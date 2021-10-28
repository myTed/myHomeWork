# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/28 08:34:54 by kyolee            #+#    #+#              #
#    Updated: 2021/10/28 09:29:22 by kyolee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= bsq
SRCS	= cal_square.c change_map.c draw_map.c utils.c getmap.c main.c
OBJS	= cal_square.o change_map.o draw_map.o utils.o getmap.o main.o
CC		= gcc
CFLAGS	= -Werror -Wall	-Wextra
HEADERS	= cal_square.h change_map.h common.h draw_map.h utils.h error.h getmap.h
all	: $(TARGET)

$(TARGET) : $(OBJS) $(HEADERS)
	$(CC) -o $@ $(OBJS) 

clean:
	rm -f *.o
	rm -f $(TARGET)

.PHONY:	clean
