/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:38:44 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/17 15:08:50 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_process1(t_pipex piping, int i, char **envp)
{
	char	*tmp;

	dup2(piping.fdfile1, STDIN_FILENO);
	dup2(piping.fd[1], STDOUT_FILENO);
	close(piping.fd[0]);
	close(piping.fd[1]);
	close(piping.fdfile1);
	close(piping.fdfile2);
	while (piping.paths[i])
	{
		piping.path = ft_strjoin(piping.paths[i], "/");
		tmp = piping.path;
		piping.path = ft_strjoin(piping.path, piping.argvsplit1[0]);
		free(tmp);
		execve(piping.path, piping.argvsplit1, envp);
		free(piping.path);
		i++;
	}
	dup2(piping.original_fd_stdout, STDOUT_FILENO);
	printf("%s : command not found\n", piping.argvsplit1[0]);
	ft_free(piping.argvsplit1);
	ft_free(piping.argvsplit2);
	ft_free(piping.paths);
	exit (1);
}

int	child_process2(t_pipex piping, int i, char **envp)
{
	char	*tmp;

	dup2(piping.fdfile2, STDOUT_FILENO);
	dup2(piping.fd[0], STDIN_FILENO);
	close(piping.fd[0]);
	close(piping.fd[1]);
	close(piping.fdfile2);
	close(piping.fdfile1);
	while (piping.paths[i])
	{
		piping.path = ft_strjoin(piping.paths[i], "/");
		tmp = piping.path;
		piping.path = ft_strjoin(piping.path, piping.argvsplit2[0]);
		free(tmp);
		execve(piping.path, piping.argvsplit2, envp);
		free(piping.path);
		i++;
	}
	dup2(piping.original_fd_stdout, STDOUT_FILENO);
	printf("%s : command not found\n", piping.argvsplit2[0]);
	ft_free(piping.argvsplit1);
	ft_free(piping.argvsplit2);
	ft_free(piping.paths);
	exit (1);
}
