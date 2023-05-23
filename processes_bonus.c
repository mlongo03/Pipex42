/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:38:44 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/23 11:02:49 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_fds(t_pipex *piping, int numpipe)
{
	int	i;

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
		piping->fdfile2 = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		piping->fdfile2 = open(argv[argc - 1],
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
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

int	child_process1(t_pipex piping, int i, char **envp)
{
	char	*tmp;

	dup2(piping.fdfile1, STDIN_FILENO);
	dup2(*(piping.fd + 1), STDOUT_FILENO);
	close_fds(&piping, piping.argc - 4 - piping.here_doc);
	execve(piping.comandsplits[0][0], piping.comandsplits[0], piping.envp);
	while (piping.paths[i])
	{
		piping.path = ft_strjoin(piping.paths[i], "/");
		tmp = piping.path;
		piping.path = ft_strjoin(piping.path, piping.comandsplits[0][0]);
		free(tmp);
		execve(piping.path, piping.comandsplits[0], envp);
		free(piping.path);
		i++;
	}
	dup2(piping.original_fd_stdout, STDOUT_FILENO);
	printf("%s : command not found\n", piping.comandsplits[0][0]);
	exit (1);
}

int	child_process2(t_pipex piping, int i, int j)
{
	char	*tmp;

	if (piping.flag == 1)
		dup2(piping.fdfile2, STDOUT_FILENO);
	else
		dup2(*(piping.fd + ((2 * (j + 1)) + 1)), STDOUT_FILENO);
	dup2(*(piping.fd + 2 * j), STDIN_FILENO);
	close_fds(&piping, piping.argc - 4 - piping.here_doc);
	execve(piping.comandsplits[j + 1][0],
		piping.comandsplits[j + 1], piping.envp);
	while (piping.paths[i])
	{
		piping.path = ft_strjoin(piping.paths[i], "/");
		tmp = piping.path;
		piping.path = ft_strjoin(piping.path, piping.comandsplits[j + 1][0]);
		free(tmp);
		execve(piping.path, piping.comandsplits[j + 1], piping.envp);
		free(piping.path);
		i++;
	}
	dup2(piping.original_fd_stdout, STDOUT_FILENO);
	printf("%s : command not found\n", piping.comandsplits[j + 1][0]);
	exit (1);
}
