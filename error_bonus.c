/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:31:06 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/23 11:05:11 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_error(char *str)
{
	ft_printf("%s", str);
	return (1);
}

void	ft_free(char **split, int *fd)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	free(fd);
}

void	ft_free3(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	***create_comandsplits(t_pipex piping, int cmds, char **argv)
{
	char	***res;
	int		i;

	i = 0;
	res = (char ***)malloc((cmds + 1) * sizeof(char **));
	while (i < cmds)
	{
		res[i] = ft_split(argv[i + 2 + piping.here_doc], ' ');
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	ft_free2(char ***splits)
{
	int	i;

	i = 0;
	while (splits[i])
		ft_free3(splits[i++]);
	free(splits);
}
