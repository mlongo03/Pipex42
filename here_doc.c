/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:03:26 by mlongo            #+#    #+#             */
/*   Updated: 2023/05/23 11:09:00 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_error(void)
{
	ft_error("Infile error");
	exit (1);
}

void	here_doc_handle(t_pipex *piping, char **argv)
{
	char	*str;
	int		fd;

	fd = open(".helper_tmp", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		here_doc_error();
	while (1)
	{
		write(1, "heredoc> ", 9);
		str = get_next_line(0);
		if (ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0
			&& ft_strlen(str) == (ft_strlen(argv[2]) + 1))
			break ;
		write(fd, str, ft_strlen(str));
		free(str);
	}
	free(str);
	close(fd);
	piping->fdfile1 = open(".helper_tmp", O_RDONLY);
	if (piping->fdfile1 < 0)
	{
		unlink(".helper_tmp");
		here_doc_error();
	}
}
