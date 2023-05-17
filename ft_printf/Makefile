# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 19:18:35 by mlongo            #+#    #+#              #
#    Updated: 2023/04/19 11:02:41 by mlongo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a

OBJS := ft_printf.o handle_c.o handle_str.o handle_decimal.o handle_void.o handle_hexlower.o handle_hexupper.o handle_unsdec10.o

FLAGS := -Wall -Werror -Wextra

all: $(NAME)

%.o : %.c
	gcc $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	ar crs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) ${B_OBJS}

fclean: clean
	rm -f $(NAME)

re: fclean all
