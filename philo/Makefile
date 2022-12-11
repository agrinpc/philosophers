# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 17:26:12 by miahmadi          #+#    #+#              #
#    Updated: 2022/12/10 20:15:17 by miahmadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo.a
PROG = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
AR = ar rcs
RM = rm -f

FILES = main \

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))


%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(PROG): $(NAME)
	$(CC) $(CFLAGS) -g $(NAME) -o $(PROG)

$(NAME): $(OBJS)
	$(AR) $@ $^

all: $(PROG)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(PROG) $(NAME)

re: clean all

.PHONY: bonus all clean fclean re