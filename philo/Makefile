# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 18:17:42 by lrandria          #+#    #+#              #
#    Updated: 2022/06/03 06:26:29 by lrandria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -pthread
OBJS		=	$(SRCS:.c=.o)
HDR			=	./philo.h
SRCS		=	0_main.c \
				1_checking.c \
				2_initialising.c \
				3a_launch_simulation.c \
				3b_god_routine.c \
				3c_philos_routine.c \
				4a_utils_philo.c \
				4b_utils_libft.c \
				4c_utils_free.c

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

mandatory:		$(NAME)

%.o:		%.c $(HDR)
			$(CC) $(CFLAGS) -c -o $@ $< 

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re
