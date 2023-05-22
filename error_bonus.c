/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:31:06 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/22 18:43:59 by mlongo           ###   ########.fr       */
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
	while(i < cmds)
	{
		res[i] = ft_split(argv[i + 2 + piping.here_doc], ' ');
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
	if (piping->here_doc)
		unlink(".helper_tmp");
}

void	get_outfile(t_pipex *piping, char **argv, int argc)
{
	if (piping->here_doc)
		piping->fdfile2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		piping->fdfile2 = open(argv[argc-1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (piping->fdfile1 < 0)
	{
		ft_error("outfile fail");
		exit (1);
	}
}

void	get_infile(t_pipex *piping, char **argv)
{
	if (ft_strncmp("here_doc", argv[1], 8) == 0 && ft_strlen(argv[1]) == 8)
	{
		here_doc_handle(piping, argv);
		piping->here_doc = 1;
	}
	else
	{
		piping->fdfile1 = open(argv[1], O_RDONLY);
		if (piping->fdfile1 == -1)
		{
			ft_error("Infile: No such file or directory");
			exit (1);
		}
		piping->here_doc = 0;
	}
}

void	here_doc_handle(t_pipex *piping, char **argv)
{
	char	*str;
	int		fd;

	fd = open(".helper_tmp", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_error("Infile error");
		exit (1);
	}
	while (1)
	{
		write(1, "heredoc> ", 9);
		str = get_next_line(0);
		if (ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0
			&& ft_strlen(str) == (ft_strlen(argv[2]) + 1))
			break;
		write(fd, str, ft_strlen(str));
		free(str);
	}
	free(str);
	close(fd);
	piping->fdfile1 = open(".helper_tmp", O_RDONLY);
	if (piping->fdfile1 < 0)
	{
		unlink(".helper_tmp");
		ft_error("Infile error");
		exit (1);
	}
}
