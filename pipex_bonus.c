/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:44:56 by alessiolong       #+#    #+#             */
/*   Updated: 2023/05/17 19:30:56 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	piping;
	int		i;
	int		fd[argc-4][2];
	char	***comandsplits;

	if (argc < 5)
		return (ft_error("numero di argomenti non valido"));
	i = 0;
	piping.fdfile1 = open(argv[1], O_RDONLY);
	if (piping.fdfile1 == -1)
		return (ft_error("Infile: No such file or directory"));
	piping.fdfile2 = open(argv[argc-1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (piping.fdfile2 == -1)
		return (ft_error("Outfile: No such file or directory"));
	comandsplits = create_comandsplits(argc - 3, argv);
	// piping.argvsplit1 = ft_split(argv[2], ' '); va fatto dentro create comandsplits
	// piping.argvsplit2 = ft_split(argv[argc-1], ' ');
	piping.original_fd_stdout = dup(STDOUT_FILENO);
	while (argc > 4)
	{
		if (pipe(fd[argc-5]) == -1)
			return (ft_error("piping failed"));
		argc--;
	}
	split_main(&piping, i, envp);
	close(piping.fd[0]);
	close(piping.fd[1]);
	ft_free(piping.argvsplit1);
	ft_free(piping.argvsplit2);
	ft_free(piping.paths);
	waitpid(piping.pid3, NULL, 0);
}

void	split_main(t_pipex *piping, int i, char **envp)
{
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != 0)
			break ;
		i++;
	}
	piping->paths = ft_split(envp[i], ':');
	piping->paths[0] = ft_strtrim(piping->paths[0], "PATH=");
	piping->pid1 = fork ();
	if (piping->pid1 < 0)
		exit (1);
	i = 0;
	if (piping->pid1 == 0)
		child_process1(*piping, i, envp);
	waitpid(piping->pid1, NULL, 0);
	while(argc > 4) //loop per fare il fork per ogni pipe e redirectare l´output nella pipe successiva fino al file
	{
		piping->pid2 = fork();
		if (piping->pid2 < 0)
			exit (0);
		i = 0;
		if (piping->pid2 == 0)
		{
			if (argc == 5)
				flag = 1;
			else
				flag = 0;
			child_process2(*piping, i, envp, flag, argc - 5); // da vedere come calcolare il num di pipe
		}
		waitpid(piping->pid2, NULL, 0);
		argc--;
	}
}
