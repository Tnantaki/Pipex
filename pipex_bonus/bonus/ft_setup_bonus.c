/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:52:15 by tnantaki          #+#    #+#             */
/*   Updated: 2023/02/03 14:57:51 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_check_arg(int ac, char **av, t_pipe *pipex)
{
	pipex->here_doc = 0;

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			ft_prterr(ARG_ERR, NULL, 1);
		else
			pipex->here_doc = 1;
	}
	else
	{
		if (ac < 5)
			ft_prterr(ARG_ERR, NULL, 1);
	}
	pipex->cmd_nb = ac - 3 - pipex->here_doc;
	pipex->pipe_nb = pipex->cmd_nb - 1;
}

void	ft_open_infile(char **av, t_pipe *pipex)
{
	if (pipex->here_doc)
	{
		pipex->fd_in = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (pipex->fd_in == -1)
			ft_prterr(HERE_DOC, "here_doc", errno);
		pipex->len = ft_strlen(av[2]);
		while (1)
		{
			ft_putstr_fd("heredoc> ", STDOUT_FILENO);
			pipex->tmp = get_next_line(STDIN_FILENO);// Check error malloc
			if (ft_strncmp(av[2], pipex->tmp, pipex->len) == 0
				&& pipex->len + 1 == ft_strlen(pipex->tmp))
				break ;
			ft_putstr_fd(pipex->tmp, pipex->fd_in);
			free (pipex->tmp);
		}
		free (pipex->tmp);
	}
	else
	{
		pipex->fd_in = open(av[1], O_RDONLY);
		if (pipex->fd_in == -1)
			ft_prterr(NO_INFILE, av[1], errno);
	}
}

void	ft_findpath(char **envp, t_pipe *pipex)
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
	pipex->path = ft_split(tmp, ':');
	free(tmp);
	i = 0;
	while (pipex->path[i])
	{
		pipex->path[i] = ft_strjoinfree(pipex->path[i], "/");
		i++;
	}
}
