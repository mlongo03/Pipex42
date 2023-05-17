/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hexupper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:25:28 by mlongo            #+#    #+#             */
/*   Updated: 2023/04/19 16:23:25 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hexa1(unsigned int n, char *hexa, int *i)
{
	if (n < 16)
	{
		handle_c(hexa[n]);
		*i = *i + 1;
	}
	else
	{
		print_hexa1(n / 16, hexa, i);
		print_hexa1(n % 16, hexa, i);
	}
}

int	handle_hexupper(unsigned int p)
{
	char			*hexa;
	unsigned int	number;
	int				i;

	i = 0;
	number = (unsigned int)p;
	hexa = "0123456789ABCDEF";
	print_hexa1(number, hexa, &i);
	return (i);
}
