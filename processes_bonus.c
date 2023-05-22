/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:38:44 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/22 18:38:36 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	execve(piping.comandsplits[j + 1][0], piping.comandsplits[j + 1], piping.envp);
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
