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
	if (ft_strncmp(cmd[0], "/", 1) == 0 && access(cmd[0], F_OK) != 0)
	{
		ft_double_free(cmd);
		ft_double_free(path);
		ft_prterr(NO_INFILE, av, 127);
	}
	while (path[i])
	{
		fcmd = ft_strjoin(path[i], cmd[0]);
		if (access(fcmd, F_OK) == 0)
			return (ft_double_free(path), fcmd);
		free (fcmd);
		i++;
	}
	ft_double_free(cmd);
	ft_double_free(path);
	ft_prterr(COM_ERR, av, 127);
	return (NULL);
}

static void	ft_fork_child(char **av, t_pipe *pipex, char **envp)
{
	pipex->pid[pipex->i] = fork();
	if (pipex->pid[pipex->i] == -1)
		ft_fork_err(pipex, errno);
	if (pipex->pid[pipex->i] == 0)
	{
		free(pipex->pid);
		pipex->cmd_i = pipex->i + 2 + pipex->here_doc;
		if (pipex->i == 0)
			ft_first_cmd(pipex);
		else if (pipex->i == (pipex->cmd_nb - 1))
			ft_last_cmd(pipex, av);
		else if (pipex->i > 0 && pipex->i < (pipex->cmd_nb - 1))
			ft_mid_cmd(pipex);
		ft_close_pipe(pipex);
		pipex->cmd = ft_split(av[pipex->cmd_i], ' ');
		pipex->fcmd = ft_fcmd(pipex->path, pipex->cmd, av[pipex->cmd_i]);
		if (execve(pipex->fcmd, pipex->cmd, envp) == -1)
		{
			free(pipex->fcmd);
			ft_double_free(pipex->cmd);
			exit (errno);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipex;

	ft_check_arg(ac, av, &pipex);
	if (pipex.here_doc)
		ft_open_here_doc(av, &pipex);
	else
		ft_open_infile(av, &pipex);
	ft_findpath(envp, &pipex);
	ft_create_pipe(&pipex);
	pipex.i = 0;
	while (pipex.i < pipex.cmd_nb)
	{
		ft_fork_child(av, &pipex, envp);
		pipex.i++;
	}
	pipex.i = 0;
	ft_parent_free(&pipex);
	while (pipex.i < pipex.cmd_nb)
		waitpid(pipex.pid[pipex.i++], &pipex.status, 0);
	free(pipex.pid);
	return (WEXITSTATUS(pipex.status));
}
