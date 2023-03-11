# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 14:54:40 by aelsiddi          #+#    #+#              #
#    Updated: 2023/03/11 08:29:47 by aelsiddi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = libft.c\
		parsing.c\
		utility.c\
		start.c\
		action_1.c\
		action_2.c\
		flow.c\
		main.c

HEADERS = ./philo.h

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc

all: $(NAME)
$(NAME): $(OBJ)
	@$(CC) -pthread -g $(SRC) $(FLAGS) -o philo

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf philo

re: fclean all