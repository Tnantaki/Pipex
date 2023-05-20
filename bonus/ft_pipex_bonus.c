/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:53:10 by tnantaki          #+#    #+#             */
/*   Updated: 2023/02/04 19:43:36 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static char	*ft_fcmd(char **path, char **cmd, char *av)
{
	char	*fcmd;
	int		i;

	i = 0;
	if (access(cmd[0], F_OK) == 0)
		return (ft_double_free(path), fcmd = ft_strjoin("", cmd[0]));
	if (ft_strchr(cmd[0], '/') && access(cmd[0], F_OK) != 0)
	{
		ft_double_free(cmd);
		ft_double_free(path);
		ft_prterr(NO_INFILE, av, 2);
	}
	while (path[i])
	{
		fcmd = ft_strjoin(path[i], cmd[0]);
		if (access(fcmd, F_OK) == 0)
			return (ft_double_free(path), fcmd);
		free (fcmd);
		i++;
	}
	fcmd = ft_strdup(cmd[0]);
	ft_double_free(cmd);
	ft_double_free(path);
	ft_prterr(COM_ERR, fcmd, 127);
	return (NULL);
}

static void	ft_fork_child(char **av, t_pipe *px, char **envp)
{
	int pid = fork();
	if (pid == -1)
		ft_fork_err(px, errno);
	if (pid == 0)
	{
		px->cmd_i = px->i + 2 + px->here_doc;
		if (px->i == 0)
			ft_first_cmd(px, av);
		else if (px->i == (px->cmd_nb - 1))
			ft_last_cmd(px, av);
		else if (px->i > 0 && px->i < (px->cmd_nb - 1))
			ft_mid_cmd(px);
		close(px->fd_pipe[0]);
		close(px->fd_pipe[1]);
		px->cmd = ft_split(av[px->cmd_i], ' ');
		px->fcmd = ft_fcmd(px->path, px->cmd, av[px->cmd_i]);
		if (execve(px->fcmd, px->cmd, envp) == -1)
		{
			free(px->fcmd);
			ft_double_free(px->cmd);
			exit (errno);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	px;

	ft_check_arg(ac, av, &px);
	// ft_open_infile(av, &px);
	ft_findpath(envp, &px);
	if (pipe(px.fd_pipe) == -1)
		ft_prterr(PIPE_ERR, NULL, errno);
	// ft_create_pipe(&px);
	px.i = 0;
	while (px.i < px.cmd_nb)
	{
		ft_fork_child(av, &px, envp);
		px.i++;
	}
	// px.i = 0;
	// ft_parent_free(&px);
	waitpid(-1, &px.status, 0);
	// while (px.i < px.cmd_nb)
	// 	waitpid(px.pid[px.i++], &px.status, 0);
	// free(px.pid);
	if (px.here_doc)
		unlink(HERE_DOC_PATH);
	return (WEXITSTATUS(px.status));
}
