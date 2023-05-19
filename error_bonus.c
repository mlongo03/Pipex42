/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:31:06 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/18 19:23:31 by alessiolong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_error(char *str)
{
	ft_printf("%s", str);
	return (1);
}

void	ft_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	***create_comandsplits(int cmds, char **argv)
{
	char	***res;
	int		i;

	i = 0;
	res = (char ***)malloc((cmds + 1) * sizeof(char **));
	while(i < cmds)
	{
		res[i] = ft_split(argv[i + 2], ' ');
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	ft_free2(char ***splits)
{
	int i;

	i = 0;
	while (splits[i])
		ft_free(splits[i++]);
	free(splits);
}

void	close_fds(t_pipex *piping, int fd[][2], int num)
{
	int i;

	i = 0;
	close(piping->fdfile1);
	close(piping->fdfile2);
	while (i < num)
	{
		close(fd[i][1]);
		close(fd[i][0]);
		i++;
	}
}
