# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/05 15:41:14 by ydeineha          #+#    #+#              #
#    Updated: 2018/06/05 15:41:16 by ydeineha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

LIB = ./libft/libft.a

FLAGS = -Wall -Wextra -Werror -I. -c

SRCS = reading.c clean_game.c create_node.c find_ways.c lem_in.c \
		manage_links.c move_ants.c validation_1.c validation_2.c \
		print_moves.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIB): 
	@make -C libft

$(NAME): $(LIB)
	@gcc $(SRCS) $(FLAGS)
	@gcc $(OBJS) $(LIB) -o $(NAME)
	@echo "\x1b[35mYour PROGRAM has been successfully created!\x1b[0m"

clean:
	@make -C libft clean
	@rm -rf $(OBJS)
	@echo "\x1b[36mObject files have been deleted!\x1b[0m"

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)
	@echo "\x1b[32mExecutable files have been deleted!\x1b[0m"

re: fclean all
