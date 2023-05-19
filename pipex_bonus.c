/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:44:56 by alessiolong       #+#    #+#             */
/*   Updated: 2023/05/19 17:39:15 by mlongo           ###   ########.fr       */
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
	piping.fd = (int *)malloc((argc - 4) * 2 * sizeof(int));
	i = 0;
	piping.fdfile1 = open(argv[1], O_RDONLY);
	if (piping.fdfile1 == -1)
		return (ft_error("Infile: No such file or directory"));
	piping.fdfile2 = open(argv[argc-1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (piping.fdfile2 == -1)
		return (ft_error("Outfile: No such file or directory"));
	piping.comandsplits = create_comandsplits(argc - 3, argv);
	piping.original_fd_stdout = dup(STDOUT_FILENO);
	while (argc > 4)
	{
		 if (pipe(piping.fd + 2 * i) == -1)
			return (ft_error("piping failed"));
		argc--;
	}
	i = 0;
	split_main(&piping, i, piping.argc);
	close_fds(&piping, piping.argc - 4);
	ft_free2(piping.comandsplits);
	ft_free(piping.paths, piping.fd, piping.argc - 4);
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
	while(argc > 4)
	{
		piping->pid2 = fork();
		if (piping->pid2 < 0)
			exit (0);
		i = 0;
		if (piping->pid2 == 0)
		{
			if (argc == 5)
				piping->flag = 1;
			else
				piping->flag = 0;
			child_process2(*piping, i, j++);
		}
		argc--;
	}
}
