# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lps <lps@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 12:25:01 by lps               #+#    #+#              #
#    Updated: 2024/09/19 12:25:03 by lps              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = btc

CXX = c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror 

SRCS = main.cpp BitcoinExchange.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re