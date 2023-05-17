/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:17:43 by mlongo            #+#    #+#             */
/*   Updated: 2023/04/19 17:22:46 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_case(va_list arg, char c)
{
	int	len;

	len = 0;
	if (c == 'c' || c == '%')
	{
		if (c == 'c')
			handle_c(va_arg(arg, int));
		else
			handle_c('%');
		len++;
	}
	else if (c == 's')
		len = len + handle_str(va_arg(arg, char *));
	else if (c == 'p')
		len = len + handle_void(va_arg(arg, void *));
	else if (c == 'd' || c == 'i')
		len = len + handle_decimal(va_arg(arg, int));
	else if (c == 'u')
		len = len + handle_unsdec10(va_arg(arg, unsigned int));
	else if (c == 'x')
		len = len + handle_hexlower(va_arg(arg, unsigned int));
	else if (c == 'X')
		len = len + handle_hexupper(va_arg(arg, unsigned int));
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		i;
	int		len;

	len = 0;
	i = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			len = len + handle_case(arg, str[i]);
		}
		else
		{
			write(1, &str[i], 1);
			len++;
		}
		i++;
	}
	va_end(arg);
	return (len);
}
