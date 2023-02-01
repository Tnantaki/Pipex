/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:53:10 by tnantaki          #+#    #+#             */
/*   Updated: 2023/02/02 00:28:03 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipex;

	printf("Hello\n");
	ft_check_arg(ac, av, &pipex);
	// if (ac < )
	// 	ft_prterr(ARG_ERR, NULL, 1);
	int	fd = open("infile.txt", O_RDONLY);
	printf("fd:%d\n", fd);
	char *str = get_next_line(fd);
	printf("%s", str);
	printf("%d\n", pipex.here_doc);
	printf("%d\n", pipex.cmd_nb);
	printf("%d\n", pipex.pipe_nb);
	exit (0);
	pipex.path = ft_findpath(envp);
	if (pipe(pipex.fd_pipe) == -1)
		ft_prterr(PIPE_ERR, NULL, errno);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		ft_prterr(FORK_ERR, NULL, errno);
	if (pipex.pid1 == 0)
		ft_child1(pipex.path, av, pipex.fd_pipe, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		ft_prterr(FORK_ERR, NULL, errno);
	if (pipex.pid2 == 0)
		ft_child2(pipex.path, av, pipex.fd_pipe, envp);
	close(pipex.fd_pipe[0]);
	close(pipex.fd_pipe[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &pipex.status, 0);
	ft_double_free(pipex.path);
	return (WEXITSTATUS(pipex.status));
}
