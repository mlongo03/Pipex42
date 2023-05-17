/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:26:58 by mlongo            #+#    #+#             */
/*   Updated: 2023/04/18 18:32:39 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_decimal(int n, char *dec, int *i)
{
	if (n < 0)
	{
		handle_c('-');
		*i = *i + 1;
		if (n == -2147483648)
		{
			handle_c('2');
			*i = *i + 1;
			n = 147483648;
		}
		else
			n = -n;
	}
	if (n < 10)
	{
		handle_c(dec[n]);
		*i = *i + 1;
	}
	else
	{
		print_decimal(n / 10, dec, i);
		print_decimal(n % 10, dec, i);
	}
}

int	handle_decimal(int n)
{
	char	*dec;
	int		i;

	i = 0;
	dec = "0123456789";
	print_decimal(n, dec, &i);
	return (i);
}
