/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:31:06 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/17 12:53:36 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(char *str)
{
	printf("%s", str);
	return (1);
}

int	ft_free(char **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	if (split[i] == NULL)
	{
		while (i)
			free(split[i--]);
		free(split);
		return (1);
	}
	return (0);
}
