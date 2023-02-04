/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:46:07 by tnantaki          #+#    #+#             */
/*   Updated: 2023/01/30 23:46:12 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_double_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free (ptr[i]);
		i++;
	}
	free (ptr);
}

void	ft_parent_free(t_pipe *pipex)
{
	if (pipex->here_doc)
		unlink(HERE_DOC_PATH);
	close(pipex->fd_in);
	ft_close_pipe(pipex);
	ft_double_free(pipex->path);
}

void	ft_fork_err(t_pipe *pipex, int errnum)
{
	ft_parent_free(pipex);
	free(pipex->pid);
	ft_prterr(FORK_ERR, NULL, errnum);
}

void	ft_gnl_err(t_pipe *pipex)
{
	close(pipex->fd_in);
	unlink(HERE_DOC_PATH);
	ft_prterr(HERE_DOC, HERE_DOC_PATH, 1);
}


void	ft_prterr(int err, char *msg, int errnum)
{
	if (err == 1)
		ft_putstr_fd("Invalid number of argument.\n", STDERR_FILENO);
	else if (err == 2)
		perror("Pipe error :");
	else if (err == 3)
		perror("Fork error :");
	else if (err == 4)
	{
		ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	else if (err == 5)
	{
		ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	else if (err == 6)
	{
		ft_putstr_fd("zsh: command not found: ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	else if (err == 7)
		perror(msg);
	exit (errnum);
}
