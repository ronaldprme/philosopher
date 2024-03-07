# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 14:02:27 by isbraz-d          #+#    #+#              #
#    Updated: 2024/02/19 10:44:34 by isbraz-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CFLAGS	=  -pthread -g -Wall -Wextra -Werror #-fsanitize=thread

SRCS	= 	main.c utils.c utils_philo.c init.c actions.c manage.c quit.c 

OBJS	=	$(SRCS:%.c=%.o)

RM			=	rm -f

# /* ~~~~~~~ Colors ~~~~~~~ */
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"

all:		$(NAME)

$(NAME):	$(OBJS)
	@echo $(CYAN) " - Compiling $@" $(RED)
	$(CC) $(SRCS) $(CFLAGS) -o $(NAME)

clean:
	@echo $(PURPLE) "[Cleaning...]" $(EOC) 
	$(RM) $(OBJS)

fclean:		clean
	@echo $(PURPLE) "[FCleaning...]" $(EOC)
	$(RM) $(NAME)

re:	fclean all

.PHONY:		all clean fclean re