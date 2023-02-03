/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:53:10 by tnantaki          #+#    #+#             */
/*   Updated: 2023/02/03 17:29:37 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	ft_child(t_pipe *pipex, char **av, char **envp)
{
	char	*fcmd;
	char	**cmd;

	cmd = ft_split(av[pipex->cmd_i], ' ');
	fcmd = ft_fcmd(pipex->path, cmd, av[pipex->cmd_i]);
	if (execve(fcmd, cmd, envp) == -1)
	{
		free(fcmd);
		ft_double_free(cmd);
		exit (errno);
	}
}

void	ft_first_cmd(t_pipe *pipex)
{
	pipex->fd_read = pipex->fd_in;
	pipex->fd_write = pipex->fd_pipe[1];
	dup2(pipex->fd_read, STDIN_FILENO);
	dup2(pipex->fd_write, STDOUT_FILENO);
	close(pipex->fd_in);
}

void	ft_last_cmd(t_pipe *pipex, char **av)
{
	int	out_i;

	out_i = pipex->i + 3 + pipex->here_doc;
	pipex->fd_out = open(av[out_i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->fd_out == -1)
	{
		ft_double_free(pipex->path);
		ft_prterr(NO_OUTFILE, av[out_i], 1);
	}
	printf("out_i:%d\n", out_i);
	printf("fd_out:%d\n", pipex->fd_out);
	pipex->fd_read = pipex->fd_pipe[(pipex->i - 1) * 2];
	pipex->fd_write = pipex->fd_out;
	dup2(pipex->fd_read, STDIN_FILENO);
	dup2(pipex->fd_write, STDOUT_FILENO);
	close(pipex->fd_out);
}

void	ft_mid_cmd(t_pipe *pipex)
{
	pipex->fd_read = pipex->fd_pipe[pipex->i * 2];
	pipex->fd_write = pipex->fd_pipe[(pipex->i * 2) + 1];
	dup2(pipex->fd_read, STDIN_FILENO);
	dup2(pipex->fd_write, STDOUT_FILENO);
}

void	ft_fork_child(char **av, t_pipe *pipex, char **envp)
{
	printf("i:%d\n", pipex->i);
	printf("cmd_nb:%d\n", pipex->cmd_nb);
	pipex->pid = fork();
	if (pipex->pid == -1)
		ft_prterr(FORK_ERR, NULL, errno);
	if (pipex->pid == 0)
	{
		pipex->cmd_i = pipex->i + 2 + pipex->here_doc;
		if (pipex->i == 0) //First
			ft_first_cmd(pipex);
		else if (pipex->i == (pipex->cmd_nb - 1)) //Last
			ft_last_cmd(pipex, av);
		else if (pipex->i > 0 && pipex->i < (pipex->cmd_nb - 1)) //between
			ft_mid_cmd(pipex);
		ft_close_pipe(*pipex);
		ft_child(pipex, av, envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipex;

	ft_check_arg(ac, av, &pipex);
	ft_open_infile(av, &pipex);
	ft_create_pipe(&pipex);
	ft_findpath(envp, &pipex);
	// for (int i = 0;*pipex.path;i++)
	// 	printf("%s\n", *pipex.path++);
	printf("fd_open:%d\n", pipex.fd_in);
	pipex.i = 0;
	while (pipex.i < pipex.cmd_nb)
	{
		ft_fork_child(av, &pipex, envp);
		pipex.i++;
	}
	// ft_close_pipe(pipex);
	// waitpid(pipex.pid1, NULL, 0);
	// waitpid(pipex.pid2, &pipex.status, 0);
	// ft_double_free(pipex.path);
	// return (WEXITSTATUS(pipex.status));
	return (0);
}
