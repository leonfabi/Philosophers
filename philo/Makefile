# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 14:48:12 by fkrug             #+#    #+#              #
#    Updated: 2023/07/14 12:04:51 by fkrug            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo

OPSYS := $(shell uname)
ifeq ($(OPSYS), Linux)
	CC := gcc
	DB := gdb
else ifeq ($(OPSYS), Darwin)
	CC := cc
	DB := lldb
endif
CFLAGS := 
#-Wextra -Wall -Werror 
HEADERS	:= -I ./include
SRCS	:= main.c ft_utils.c ft_utils_2.c ft_init.c ft_threads.c
OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) -pthread -o $(NAME)

$(OBJS): %.o:%.c
	@$(CC) $(CFLAGS) -c $< $(HEADERS) -o $@ && printf "Compiling: $(notdir $<)\n"

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re