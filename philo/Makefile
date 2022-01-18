# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/20 07:03:37 by rcorenti          #+#    #+#              #
#    Updated: 2022/01/18 03:04:22 by rcorenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = clang

FLAGS = -Wall -Wextra -Werror
 

THREAD_F = -lpthread

HEADER = -I includes

srcs =	main.c\
	init.c\
	philosophers.c\
	utils.c

OBJS = ${addprefix srcs/,${srcs:.c=.o}}

.c.o :
	${CC} ${FLAGS} ${HEADER} -c $< -o ${<:.c=.o}

all : $(NAME)

${NAME}: $(OBJS)
	${CC} ${FLAGS} ${OBJS} ${THREAD_F} -o ${NAME}

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
