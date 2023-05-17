/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:14:11 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/17 15:29:30 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"

typedef struct s_pipex
{
	int		fdfile1;
	int		fdfile2;
	int		pid1;
	int		pid2;
	int		fd[2];
	char	**argvsplit1;
	char	**argvsplit2;
	char	**paths;
	char	*path;
	int		original_fd_stdout;
}	t_pipex;

int		ft_error(char *str);
int		child_process1(t_pipex pipe, int i, char **envp);
int		child_process2(t_pipex pipe, int i, char **envp);
void	ft_free(char **split);
void	split_main(t_pipex *piping, int i, char **envp);

#endif
