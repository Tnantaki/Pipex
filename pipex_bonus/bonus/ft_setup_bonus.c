/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:52:15 by tnantaki          #+#    #+#             */
/*   Updated: 2023/02/25 23:16:01 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_check_arg(int ac, char **av, t_pipe *px)
{
	px->here_doc = 0;
	if (ac < 2)
		ft_prterr(ARG_ERR, NULL, 1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && ft_strlen(av[1]) == 8)
	{
		if (ac < 6)
			ft_prterr(ARG_ERR, NULL, 1);
		else
			px->here_doc = 1;
	}
	else
	{
		if (ac < 5)
			ft_prterr(ARG_ERR, NULL, 1);
	}
	px->cmd_nb = ac - 3 - px->here_doc;
	px->pipe_nb = px->cmd_nb - 1;
}

void	ft_findpath(char **envp, t_pipe *px)
{
	char	*tmp;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
		&& envp[i][2] == 'T' && envp[i][3] == 'H')
			break ;
		i++;
	}
	tmp = ft_strtrim(envp[i], "PATH=");
	px->path = ft_split(tmp, ':');
	if (tmp)
		free(tmp);
	i = 0;
	while (px->path[i])
	{
		px->path[i] = ft_strjoinfree(px->path[i], "/");
		i++;
	}
}

static void	ft_create_here_doc(char **av, t_pipe *px)
{
	char	*tmp;
	int		fd;
	int		len;

	fd = open(HERE_DOC_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		ft_prterr(HERE_DOC, HERE_DOC_PATH, errno);
	len = ft_strlen(av[2]);
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		tmp = get_next_line(STDIN_FILENO);
		if (!(tmp))
			ft_gnl_err(px);
		if (ft_strncmp(av[2], tmp, len) == 0 && tmp[len] == '\n')
			break ;
		ft_putstr_fd(tmp, fd);
		free (tmp);
	}
	free (tmp);
	close(fd);
}

void	ft_open_infile(char **av, t_pipe *px)
{
	if (px->here_doc)
	{
		ft_create_here_doc(av, px);
		px->fd_in = open(HERE_DOC_PATH, O_RDONLY);
		if (px->fd_in == -1)
		{
			unlink(HERE_DOC_PATH);
			ft_prterr(HERE_DOC, HERE_DOC_PATH, errno);
		}
	}
	else
	{
		px->fd_in = open(av[1], O_RDONLY);
		if (px->fd_in == -1)
			ft_prterr(NO_INFILE, av[1], 0);
	}
}
