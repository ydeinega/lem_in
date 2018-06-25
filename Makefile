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

SRCS = reading.c clean_game.c create_node.c find_ways.c lem_in.c manage_links.c move_ants.c validation.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIB): 
	@make -C libft.a

$(NAME): $(LIB)
	@gcc $(SRCS) $(FLAGS)
	@gcc $(OBJS) $(LIB) -o $(NAME)

clean:
	@make -C libft clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)

re: fclean all
