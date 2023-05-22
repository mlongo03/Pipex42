/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:44:56 by alessiolong       #+#    #+#             */
/*   Updated: 2023/05/22 18:50:59 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	piping;
	int		i;

	piping.envp = envp;
	piping.argc = argc;
	if (argc < 5)
		return (ft_error("numero di argomenti non valido"));
	get_infile(&piping, argv);
	get_outfile(&piping, argv, argc);
	piping.fd = (int *)malloc((argc - 4 - piping.here_doc) * 2 * sizeof(int));
	piping.comandsplits = create_comandsplits(piping, argc - 3 - piping.here_doc, argv);
	piping.original_fd_stdout = dup(STDOUT_FILENO);
	i = 0;
	while (argc-- > (4 + piping.here_doc))
	{
		if (pipe(piping.fd + 2 * i) == -1)
			return (ft_error("piping failed"));
		i++;
	}
	i = 0;
	split_main(&piping, i, piping.argc);
	close_fds(&piping, piping.argc - 4 - piping.here_doc);
	ft_free2(piping.comandsplits);
	ft_free(piping.paths, piping.fd);
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
