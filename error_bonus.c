/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:31:06 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/20 18:33:32 by alessiolong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_error(char *str)
{
	ft_printf("%s", str);
	return (1);
}

void	ft_free(char **split, int *fd, int numpipe)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	i = 0;
	while (i < (numpipe * 2))
		free(&fd[i++]);
 }

void	ft_free3(char **split)
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
		ft_free3(splits[i++]);
	free(splits);
}

void	close_fds(t_pipex *piping, int numpipe)
{
	int i;

	i = 0;
	close(piping->fdfile1);
	close(piping->fdfile2);
	while (i < (numpipe * 2))
		close(piping->fd[i++]);
}
