# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 17:09:03 by mlongo            #+#    #+#              #
#    Updated: 2023/05/17 15:01:00 by mlongo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

OBJS := pipex.o processes.o error.o

LIBFT_PATH = ./libft

LIBFT = ${LIBFT_PATH}/libft.a

FT_PRINTF_PATH = ./ft_printf

FT_PRINTF = ${FT_PRINTF_PATH}/libftprintf.a

FLAGS := -Wall -Werror -Wextra

all: $(NAME)

%.o : %.c
	cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	make -C ft_printf
	cc $(OBJS) ${LIBFT} $(FT_PRINTF) -o $(NAME) -fsanitize=address

clean:
	make clean -C libft
	make clean -C ft_printf
	rm -f $(OBJS) ${B_OBJS}

fclean: clean
	make fclean -C libft
	make fclean -C ft_printf
	rm -f $(NAME)

re: fclean all
