/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:38:44 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/19 17:40:57 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	child_process1(t_pipex piping, int i, char **envp)
{
	char	*tmp;
		// char	res[20];

	dup2(piping.fdfile1, STDIN_FILENO);
	dup2(piping.fd + 2, STDOUT_FILENO);
	// read(STDIN_FILENO, res, 2);
	// write(piping.original_fd_stdout, &res, ft_strlen(res));
	close_fds(&piping, piping.argc - 4);
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
	ft_free2(piping.comandsplits);
	ft_free(piping.paths, piping.fd, piping.argc - 4);
	exit (1);
}

int	child_process2(t_pipex piping, int i, int j)
{
	char	*tmp;
	// char	res[20];

	if (piping.flag == 1)
		dup2(piping.fdfile2, STDOUT_FILENO);
	else
		dup2(piping.fd + 2 * (i + 1), STDOUT_FILENO);
	dup2(piping.fd[j][0], STDIN_FILENO);
	// read(0, res, 2);
	// write(piping.original_fd_stdout, &res, ft_strlen(res));
	close_fds(&piping, piping.argc - 4);
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
	ft_free2(piping.comandsplits);
	ft_free(piping.paths, piping.fd, piping.argc - 4);
	exit (1);
}
