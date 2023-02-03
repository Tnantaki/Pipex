/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:53:10 by tnantaki          #+#    #+#             */
/*   Updated: 2023/02/03 11:41:59 by tnantaki         ###   ########.fr       */
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

void	ft_findpath(char **envp, t_pipe *pipex)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
		&& envp[i][2] == 'T' && envp[i][3] == 'H')
			break ;
		i++;
	}
	pipex->path = ft_split(ft_strtrim(envp[i], "PATH="), ':');
	i = 0;
	while (pipex->path[i])
	{
		pipex->path[i] = ft_strjoinfree(pipex->path[i], "/");
		i++;
	}
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
			pipex->tmp = get_next_line(STDIN_FILENO);// Don't forget to check error malloc
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

void	ft_fork_child(char **av, t_pipe pipex, char **envp)
{
	int	i;

	i = 0;
	while (i < pipex.cmd_nb)
	{
		pipex.pid = fork();
		if (pipex.pid == -1)
			ft_prterr(FORK_ERR, NULL, errno);
		if (pipex.pid == 0)
		{
			if (i == 0) //First
			{
				dup2(pipex.fd_in, STDIN_FILENO);
				dup2(pipex.fd_pipe[1], STDOUT_FILENO);
				ft_child1(pipex.path, av, pipex.fd_pipe, envp);
			}
			else if (i == (pipex.cmd_nb - 1)) //Last
			{
				dup2(fd_pipe[0], STDIN_FILENO);
				dup2(pipex.fd_out, STDOUT_FILENO);
				ft_child1(pipex.path, av, pipex.fd_pipe, envp);
			}
			else if (i > 0 && i i < (pipex.cmd_nb - 1)) //between
				ft_child1(pipex.path, av, pipex.fd_pipe, envp);
		}
		i++;
	}

	//old//
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
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipex;

	ft_check_arg(ac, av, &pipex);
	ft_open_infile(av, &pipex);
	ft_create_pipe(&pipex);
	ft_findpath(envp, &pipex);
	for (int i = 0;*pipex.path;i++)
		printf("%s\n", *pipex.path++);
	exit (0);
	ft_fork_child(av, pipex, envp);
	ft_close_pipe(pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &pipex.status, 0);
	ft_double_free(pipex.path);
	return (WEXITSTATUS(pipex.status));
}
