# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ranki <ranki@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/19 21:11:40 by ranki             #+#    #+#              #
#    Updated: 2024/07/27 22:11:01 by ranki            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = main.cpp BitcoinExchange.cpp\

HEAD = BitcoinExchange.hpp\

OBJS = $(SRCS:.cpp=.o)

NAME = btc

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