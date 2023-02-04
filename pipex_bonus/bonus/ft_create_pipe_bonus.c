/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipe_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:17:00 by tnantaki          #+#    #+#             */
/*   Updated: 2023/02/04 11:04:14 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_create_pipe(t_pipe *pipex)
{
	int	i;

	i = 0;
	pipex->fd_pipe = malloc(sizeof(int) * (pipex->pipe_nb * 2));
	pipex->pid = malloc(sizeof(int) * (pipex->cmd_nb));
	if (!(pipex->fd_pipe) || !(pipex->pid))
	{
		unlink(HERE_DOC_PATH);
		ft_double_free(pipex->path);
		ft_prterr(PIPE_ERR, NULL, errno);
	}
	while (i < pipex->pipe_nb)
	{
		if (pipe(pipex->fd_pipe + (i * 2)) == -1)
		{
			unlink(HERE_DOC_PATH);
			ft_double_free(pipex->path);
			ft_prterr(PIPE_ERR, NULL, errno);
		}
		i++;
	}
}

void	ft_close_pipe(t_pipe *pipex)
{
	int	i;
	int	fd_pipe_nb;

	i = 0;
	fd_pipe_nb = pipex->pipe_nb *2;
	while (i < fd_pipe_nb)
	{
		close(pipex->fd_pipe[i]);
		i++;
	}
	free (pipex->fd_pipe);
}
