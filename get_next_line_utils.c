/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:17:33 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/22 16:58:09 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen1( char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero1(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *) s)[i++] = 0;
}

void	*ft_calloc1(int count, int size)
{
	void	*res;
	int		len;

	len = count * size;
	res = (void *) malloc(len);
	if (res == NULL)
		return (NULL);
	ft_bzero1(res, len);
	return (res);
}

void	*ft_memcpy1(void *dst, const void *src, int n)
{
	const char	*s;
	char		*d;

	d = dst;
	s = src;
	if (!d && !s)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dst);
}
