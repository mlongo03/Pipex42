# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 17:09:03 by mlongo            #+#    #+#              #
#    Updated: 2023/05/16 12:56:21 by alessiolong      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

OBJS := test.o

LIBFT_PATH = ./libft

LIBFT = ${LIBFT_PATH}/libft.a

FLAGS := -Wall -Werror -Wextra

all: $(NAME)

%.o : %.c
	cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	cc $(OBJS) ${LIBFT} -o $(NAME)

clean:
	make clean -C libft
	rm -f $(OBJS) ${B_OBJS} $(LIBFT)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
