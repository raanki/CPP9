# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ranki <ranki@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/19 21:11:40 by ranki             #+#    #+#              #
#    Updated: 2024/08/28 08:57:54 by ranki            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = main.cpp PmergeMe.cpp\

HEAD = PmergeMe.hpp\

OBJS = $(SRCS:.cpp=.o)

NAME = PmergeMe

CC = c++ -Wall -Wextra -Werror -Iincludes -std=c++98

all: $(NAME)

$(NAME): $(OBJS) $(HEAD)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re