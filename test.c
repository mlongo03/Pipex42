/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:44:56 by alessiolong       #+#    #+#             */
/*   Updated: 2023/05/16 15:17:27 by alessiolong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int 	i;
	int 	fdfile1;
	int 	fdfile2;
	int 	fd[2];
	char	**argvsplit1;
	char	**argvsplit2;
	char	**paths;
	char	*path;
	int		original_fd_stdout;

	if (argc != 5)
	{
		printf("numero di argomenti non valido");
		return 1;
	}
	i = 0;
	fdfile1 = open(argv[1], O_RDONLY);
	if (fdfile1 == -1)
	{
		printf("Infile: No such file or directory");
		return 1;
	}
	fdfile2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT);
	argvsplit1 = ft_split(argv[2], ' ');
	argvsplit2 = ft_split(argv[3], ' ');
	original_fd_stdout = dup(STDOUT_FILENO);
	if (pipe(fd) == -1 || fdfile1 == -1 || fdfile2 == -1)
		return (0);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != 0)
			break;
		i++;
	}
	paths = ft_split(envp[i], ':');
	paths[0] = ft_strtrim(paths[0], "PATH=");
	int pid1 = fork();
	if (pid1 < 0)
		return (0);
	i = 0;
	if (pid1 == 0)
	{
		dup2(fdfile1, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(fdfile1);
		close(fdfile2);
		while (paths[i])
		{
			path = ft_strjoin(paths[i], "/");
			path = ft_strjoin(path, argvsplit1[0]);
			execve(path, argvsplit1, envp);
			i++;
		}
		dup2(original_fd_stdout, STDOUT_FILENO);
		printf("%s : command not found\n", argvsplit1[0]);
		return 1;
	}
	waitpid(pid1, NULL, 0);
	int pid2 = fork();
	if (pid2 < 0)
		return (0);
	i = 0;
	if (pid2 == 0)
	{

		dup2(fdfile2, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(fdfile2);
		close(fdfile1);
		while (paths[i])
		{
			path = ft_strjoin(paths[i], "/");
			path = ft_strjoin(path, argvsplit2[0]);
			execve(path, argvsplit2, envp);
			i++;
		}
		dup2(original_fd_stdout, STDOUT_FILENO);
		printf("%s : command not found\n", argvsplit2[0]);
		return 1;
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid2, NULL, 0);
}
