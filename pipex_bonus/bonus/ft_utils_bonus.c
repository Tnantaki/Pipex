/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:35:01 by tnantaki          #+#    #+#             */
/*   Updated: 2023/02/09 10:35:10 by tnantaki         ###   ########.fr       */
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
		msg = ft_strjoin(msg, ": no such file or directory\n");
	else if (err == 5)
		msg = ft_strjoin(msg, ": no such file or directory\n");
	else if (err == 6)
		msg = ft_strjoinfree(msg, ": command not found\n");
	else if (err == 7)
		perror(msg);
	if (msg && (err == 4 || err == 5 || err == 6))
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
	}
	if (err == 4)
		return ;
	exit (errnum);
}
