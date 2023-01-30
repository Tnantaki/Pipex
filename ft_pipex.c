/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:53:10 by tnantaki          #+#    #+#             */
/*   Updated: 2023/01/30 23:56:00 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_fcmd(char **path, char **cmd, char *av)
{
	char	*fcmd;
	int		i;

	i = 0;
	if (access(cmd[0], F_OK) == 0)
	{
		fcmd = ft_strjoin("", cmd[0]);
		ft_double_free(path);
		return (fcmd);
	}
	while (path[i])
	{
		fcmd = ft_strjoin(path[i], cmd[0]);
		if (access(fcmd, F_OK) == 0)
		{
			ft_double_free(path);
			return (fcmd);
		}
		free (fcmd);
		i++;
	}
	ft_double_free(cmd);
	ft_double_free(path);
	ft_prterr(COM_ERR, av);
	return (NULL);
}

static void	ft_child(char **path, char **av, int *fd_pipe, char **envp)
{
	char	*fcmd;
	char	**cmd;
	int		fd_in;

	fd_in = open (av[1], O_RDONLY);
	if (fd_in == -1)
	{
		ft_double_free(path);
		ft_prterr(NO_FILE, av[1]);
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	close(fd_pipe[0]);
	close(fd_in);
	cmd = ft_split(av[2], ' ');
	fcmd = ft_fcmd(path, cmd, av[2]);
	if (execve(fcmd, cmd, envp) == -1)
	{
		free(fcmd);
		ft_double_free(cmd);
		exit (errno);
	}
}

static void	ft_parent(char **path, char **av, int *fd_pipe, char **envp)
{
	char	*fcmd;
	char	**cmd;
	int		fd_out;

	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
	{
		ft_double_free(path);
		ft_prterr(NO_FILE, av[4]);
	}
	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(fd_pipe[1]);
	close(fd_pipe[0]);
	cmd = ft_split(av[3], ' ');
	fcmd = ft_fcmd(path, cmd, av[3]);
	if (execve(fcmd, cmd, envp) == -1)
	{
		free(fcmd);
		ft_double_free(cmd);
		exit (errno);
	}
}

static char	**ft_findpath(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
		&& envp[i][2] == 'T' && envp[i][3] == 'H')
			break ;
		i++;
	}
	path = ft_split(ft_strtrim(envp[i], "PATH="), ':');
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoinfree(path[i], "/");
		i++;
	}
	return (path);
}

int	main(int ac, char **av, char **envp)
{
	char	**path;
	int		fd_pipe[2];
	int		pid;

	if (ac != 5)
		ft_prterr(ARG_ERR, NULL);
	path = ft_findpath(envp);
	if (pipe(fd_pipe) == -1)
		ft_prterr(PIPE_ERR, NULL);
	pid = fork();
	if (pid == -1)
		ft_prterr(FORK_ERR, NULL);
	if (pid == 0)
		ft_child(path, av, fd_pipe, envp);
	ft_parent(path, av, fd_pipe, envp);
	ft_double_free(path);
	return (0);
}
