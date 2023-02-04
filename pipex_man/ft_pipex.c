/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:53:10 by tnantaki          #+#    #+#             */
/*   Updated: 2023/02/05 00:41:43 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static void	ft_child1(char **path, char **av, int *fd_pipe, char **envp)
{
	char	*fcmd;
	char	**cmd;
	int		fd_in;

	fd_in = open (av[1], O_RDONLY);
	if (fd_in == -1)
	{
		ft_double_free(path);
		ft_prterr(NO_INFILE, av[1], errno);
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

static void	ft_child2(char **path, char **av, int *fd_pipe, char **envp)
{
	char	*fcmd;
	char	**cmd;
	int		fd_out;

	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
	{
		ft_double_free(path);
		ft_prterr(NO_OUTFILE, av[4], 1);
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
	path = ft_split(tmp, ':');
	if (tmp)
		free(tmp);
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
	t_pipe	mypipex;

	if (ac != 5)
		ft_prterr(ARG_ERR, NULL, 1);
	mypipex.path = ft_findpath(envp);
	if (pipe(mypipex.fd_pipe) == -1)
		ft_prterr(PIPE_ERR, NULL, errno);
	mypipex.pid1 = fork();
	if (mypipex.pid1 == -1)
		ft_prterr(FORK_ERR, NULL, errno);
	if (mypipex.pid1 == 0)
		ft_child1(mypipex.path, av, mypipex.fd_pipe, envp);
	mypipex.pid2 = fork();
	if (mypipex.pid2 == -1)
		ft_prterr(FORK_ERR, NULL, errno);
	if (mypipex.pid2 == 0)
		ft_child2(mypipex.path, av, mypipex.fd_pipe, envp);
	close(mypipex.fd_pipe[0]);
	close(mypipex.fd_pipe[1]);
	waitpid(mypipex.pid1, NULL, 0);
	waitpid(mypipex.pid2, &mypipex.status, 0);
	ft_double_free(mypipex.path);
	return (WEXITSTATUS(mypipex.status));
}
