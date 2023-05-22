/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:41:27 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/22 16:51:28 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

void	ft_bzero1(void *s, size_t n);
void	*ft_memcpy1(void *dst, const void *src, int n);
void	*ft_calloc1(int count, int size);
char	*get_next_line(int fd);
int		ft_strlen1(char *str);

#endif
