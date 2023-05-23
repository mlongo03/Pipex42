# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 17:09:03 by mlongo            #+#    #+#              #
#    Updated: 2023/05/23 11:40:52 by mlongo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

OBJS := pipex.o processes.o error.o

OBJS_BONUS := pipex_bonus.o processes_bonus.o error_bonus.o get_next_line.o get_next_line_utils.o here_doc.o

LIBFT_PATH = ./libft

LIBFT = ${LIBFT_PATH}/libft.a

FT_PRINTF_PATH = ./ft_printf

FT_PRINTF = ${FT_PRINTF_PATH}/libftprintf.a

FLAGS := -Wall -Werror -Wextra

#COLORS
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

DEFAULT = \033[0m

all: $(NAME)

bonus: $(OBJS_BONUS)
	@make -C libft
	@make -C ft_printf
	@cc $(OBJS_BONUS) ${LIBFT} $(FT_PRINTF) -o $(NAME)
	@echo "$(GREEN)$(NAME) bonus created!$(DEFAULT)"

%.o : %.c
	@cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@make -C libft
	@make -C ft_printf
	@cc $(OBJS) ${LIBFT} $(FT_PRINTF) -o $(NAME)
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	@make clean -C libft
	@make clean -C ft_printf
	@rm -f $(OBJS) ${OBJS_BONUS}
	@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@make fclean -C libft
	@make fclean -C ft_printf
	@rm -f $(NAME)
	@echo "$(RED)all deleted!$(DEFAULT)"

re: bonus clean fclean all
