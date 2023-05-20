/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:14:11 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/20 18:12:13 by alessiolong      ###   ########.fr       */
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
	pid_t		pid2;
	pid_t		pid3;
	int		*fd;
	char	**paths;
	char	*path;
	int		original_fd_stdout;
	int		flag;
	int		argc;
	char	**envp;
	char	***comandsplits;
}	t_pipex;

int		ft_error(char *str);
int		child_process1(t_pipex piping, int i, char **envp);
int		child_process2(t_pipex piping, int i,int j);
void	ft_free(char **split, int *fd, int numpipe);
void	ft_free2(char ***splits);
void	ft_free3(char **split);
void	split_main(t_pipex *piping, int i,int argc);
char	***create_comandsplits(int cmds, char **argv);
void	close_fds(t_pipex *piping, int numpipe);

#endif
