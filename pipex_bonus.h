/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:14:11 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/22 17:47:48 by mlongo           ###   ########.fr       */
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
# include "get_next_line.h"

typedef struct s_pipex
{
	int		here_doc;
	int		fdfile1;
	int		fdfile2;
	pid_t	pid1;
	pid_t	pid2;
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
void	ft_free(char **split, int *fd);
void	ft_free2(char ***splits);
void	ft_free3(char **split);
void	split_main(t_pipex *piping, int i,int argc);
char	***create_comandsplits(t_pipex piping, int cmds, char **argv);
void	close_fds(t_pipex *piping, int numpipe);
void	get_infile(t_pipex *piping, char **argv);
void	here_doc_handle(t_pipex *piping, char **argv);
void	get_outfile(t_pipex *piping, char **argv, int argc);

#endif
