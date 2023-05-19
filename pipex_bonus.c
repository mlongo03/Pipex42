/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:44:56 by alessiolong       #+#    #+#             */
/*   Updated: 2023/05/18 20:20:22 by alessiolong      ###   ########.fr       */
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
	int		fd[argc-4][2];
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
		if (pipe(fd[argc-5]) == -1)
			return (ft_error("piping failed"));
		argc--;
	}
	split_main(&piping, i, fd, piping.argc);
	close_fds(&piping, fd, piping.argc - 4);
	ft_free2(piping.comandsplits);
	ft_free(piping.paths);
}

void	split_main(t_pipex *piping, int i, int fd[][2], int argc)
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
		child_process1(*piping, i, piping->envp, fd);
	waitpid(piping->pid1, NULL, 0);
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
			child_process2(*piping, i, fd, j++);
		}
		waitpid(piping->pid2, NULL, 0);
		argc--;
	}
}
