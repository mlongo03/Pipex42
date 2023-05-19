/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:14:11 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/18 19:21:22 by alessiolong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	char	**paths;
	char	*path;
	int		original_fd_stdout;
	int		flag;
	int		argc;
	char	**envp;
	char	***comandsplits;
}	t_pipex;

int		ft_error(char *str);
int		child_process1(t_pipex piping, int i, char **envp, int fd[][2]);
int		child_process2(t_pipex piping, int i, int fd[][2], int j);
void	ft_free(char **split);
void	ft_free2(char ***splits);
void	split_main(t_pipex *piping, int i, int fd[][2], int argc);
char	***create_comandsplits(int cmds, char **argv);
void	close_fds(t_pipex *piping, int fd[][2], int num);

#endif
