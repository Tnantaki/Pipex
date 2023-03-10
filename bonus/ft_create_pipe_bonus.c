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

void	ft_create_pipe(t_pipe *px)
{
	px->i = 0;
	px->fd_pipe = malloc(sizeof(int) * (px->pipe_nb * 2));
	px->pid = malloc(sizeof(int) * (px->cmd_nb));
	if (!(px->fd_pipe) || !(px->pid))
	{
		ft_double_free(px->path);
		close(px->fd_in);
		if (px->here_doc)
			unlink(HERE_DOC_PATH);
		ft_prterr(PIPE_ERR, NULL, errno);
	}
	while (px->i < px->pipe_nb)
	{
		if (pipe(px->fd_pipe + (px->i * 2)) == -1)
		{
			ft_double_free(px->path);
			close(px->fd_in);
			if (px->here_doc)
				unlink(HERE_DOC_PATH);
			free(px->fd_pipe);
			free(px->pid);
			ft_prterr(PIPE_ERR, NULL, errno);
		}
		px->i++;
	}
}

void	ft_close_pipe(t_pipe *px)
{
	int	i;
	int	fd_pipe_nb;

	i = 0;
	fd_pipe_nb = px->pipe_nb * 2;
	while (i < fd_pipe_nb)
	{
		close(px->fd_pipe[i]);
		i++;
	}
	free (px->fd_pipe);
}
