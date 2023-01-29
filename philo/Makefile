# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 14:54:40 by aelsiddi          #+#    #+#              #
#    Updated: 2023/01/24 15:57:37 by aelsiddi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SRCS		=	philo.c helper.c 

# OBJES 		= ${SRCS:.c=.o}

# NAME 		= philo
# CC 			= gcc
# CFLAGS 		= -g -Wall -Wextra -Werror
# RM 			= rm -rf


# %.o			:	%.c
# 				$(CC) ${CFLAGS} -c $< -o $@
	

# all			:	$(NAME)

# $(NAME)		:	$(OBJES) philo.h
# 				$(CC) $(OBJES) -o $(NAME)
				
# clean		:
# 				$(RM) $(OBJES)

# fclean		:	clean
# 				$(RM) $(NAME)

# re			:	clean all

# norm :
# 	norminette $(shell find *.c *.h)

# .PHONY		:	all clean fclean re

NAME = philo

FILES =	philo.c helper.c error.c init.c

HEADERS = ./philo.h

OBJ = $(FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc -pthread

R = \033[1;31m
G = \033[1;32m
Y = \033[1;33m
B = \033[1;34m
RESET = \033[0m

all: $(NAME)
$(NAME): $(OBJ)
	@echo "$(Y)——————————————————————————————————————————————————————————————$(RESET)"
	@echo "$(G)【OK】$(RESET) $(B)Compiling with the flags....$(RESET)"

	@$(CC) -pthread -g $(FILES) $(FLAGS) -o philo

	@echo "$(G)【OK】❮philo❯ CREATED$(RESET)"
	@echo "$(Y)——————————————————————————————————————————————————————————————$(RESET)"

clean:
	@echo "$(Y)——————————————————————————————————————————————————————————————$(RESET)"
	@rm -rf $(OBJ)
	@echo "\033c"
	@echo "$(G)【OK】 $(RESET)        $(R)❮philo❯ objects have been DELETED$(RESET)"
	@echo "$(Y)——————————————————————————————————————————————————————————————$(RESET)"

fclean: clean
	@rm -rf philo
	@echo "\033c"
	@echo "$(G)【OK】 $(RESET)        $(R)❮philo excutable❯ DELETED$(RESET)"
	@echo "$(Y)——————————————————————————————————————————————————————————————$(RESET)"

re: fclean all

.PHONY: all clean fclean re