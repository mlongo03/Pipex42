/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:44:56 by alessiolong       #+#    #+#             */
/*   Updated: 2023/05/23 11:04:59 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pip;
	int		i;

	pip.envp = envp;
	pip.argc = argc;
	if (argc < 5)
		return (ft_error("numero di argomenti non valido"));
	get_infile(&pip, argv);
	get_outfile(&pip, argv, argc);
	pip.fd = (int *)malloc((argc - 4 - pip.here_doc) * 2 * sizeof(int));
	pip.comandsplits = create_comandsplits(pip, argc - 3 - pip.here_doc, argv);
	pip.original_fd_stdout = dup(STDOUT_FILENO);
	i = 0;
	while (argc-- > (4 + pip.here_doc))
	{
		if (pipe(pip.fd + 2 * i) == -1)
			return (ft_error("piping failed"));
		i++;
	}
	i = 0;
	split_main(&pip, i, pip.argc);
	close_fds(&pip, pip.argc - 4 - pip.here_doc);
	ft_free2(pip.comandsplits);
	ft_free(pip.paths, pip.fd);
	waitpid(-1, NULL, 0);
}

void	split_main(t_pipex *piping, int i, int argc)
{
	int	j;

	j = 0;
	while (piping->envp[i])
	{
		if (ft_strnstr(piping->envp[i], "PATH=", 5) != 0)
			break ;
		i++;
	}
	piping->paths = ft_split(piping->envp[i], ':');
	piping->paths[0] = ft_strtrim(piping->paths[0], "PATH=");
	piping->pid1 = fork ();
	if (piping->pid1 < 0)
		exit (1);
	i = 0;
	if (piping->pid1 == 0)
		child_process1(*piping, i, piping->envp);
	split_main2(piping, i, argc, j);
}

void	split_main2(t_pipex *piping, int i, int argc, int j)
{
	while (argc > (4 + piping->here_doc))
	{
		piping->pid2 = fork();
		if (piping->pid2 < 0)
			exit (0);
		i = 0;
		if (piping->pid2 == 0)
		{
			if (argc == (5 + piping->here_doc))
				piping->flag = 1;
			else
				piping->flag = 0;
			child_process2(*piping, i, j);
		}
		j++;
		argc--;
	}
}
