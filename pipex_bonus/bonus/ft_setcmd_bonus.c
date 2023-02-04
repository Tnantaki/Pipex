/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setcmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:37:39 by tnantaki          #+#    #+#             */
/*   Updated: 2023/02/04 10:27:50 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_first_cmd(t_pipe *pipex)
{
	pipex->fd_read = pipex->fd_in;
	pipex->fd_write = pipex->fd_pipe[1];
	dup2(pipex->fd_read, STDIN_FILENO);
	dup2(pipex->fd_write, STDOUT_FILENO);
	close(pipex->fd_in);
}

void	ft_mid_cmd(t_pipe *pipex)
{
	pipex->fd_read = pipex->fd_pipe[(pipex->i - 1) * 2];
	pipex->fd_write = pipex->fd_pipe[(pipex->i * 2) + 1];
	dup2(pipex->fd_read, STDIN_FILENO);
	dup2(pipex->fd_write, STDOUT_FILENO);
}

void	ft_last_cmd(t_pipe *pipex, char **av)
{
	int	out_i;

	out_i = pipex->i + 3 + pipex->here_doc;
	pipex->fd_out = open(av[out_i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->fd_out == -1)
	{
		ft_double_free(pipex->path);
		ft_prterr(NO_OUTFILE, av[out_i], 1);
	}
	pipex->fd_read = pipex->fd_pipe[(pipex->i - 1) * 2];
	pipex->fd_write = pipex->fd_out;
	dup2(pipex->fd_read, STDIN_FILENO);
	dup2(pipex->fd_write, STDOUT_FILENO);
	close(pipex->fd_out);
}
