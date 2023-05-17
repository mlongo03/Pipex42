# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 17:09:03 by mlongo            #+#    #+#              #
#    Updated: 2023/05/17 13:02:41 by mlongo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

OBJS := test.o processes.o error.o

LIBFT_PATH = ./libft

LIBFT = ${LIBFT_PATH}/libft.a

FLAGS := -Wall -Werror -Wextra

all: $(NAME)

%.o : %.c
	cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	cc $(OBJS) ${LIBFT} -o $(NAME) -fsanitize=address

clean:
	make clean -C libft
	rm -f $(OBJS) ${B_OBJS} $(LIBFT)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
