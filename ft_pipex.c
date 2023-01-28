/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:53:10 by tnantaki          #+#    #+#             */
/*   Updated: 2022/12/12 11:30:33 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void ft_execve(char **path, char **cmd_opt, char **envp)
{
	char	*cmd;
	int		i;

	i = 0;
	while (path[i])
	{
		cmd = ft_strjoin(path[i], cmd_opt[0]);
		if (access(cmd, F_OK) == 0)
		{
			ft_double_free(path);
			if (execve(cmd, cmd_opt, envp) == -1)
			{
				free (cmd);
				break;
			}
		}
		free (cmd);
		i++;
	}
	ft_double_free(cmd_opt);
	ft_double_free(path);
}

static void ft_child(char **path, char **av, int *fd, char **envp)
{
	char	**cmd_opt;
	int		infile;

	infile = open (av[1], O_RDONLY);
	if (infile == -1)
	{
		ft_double_free(path);
		ft_prterr(NO_FILE, av[1]);
	}
	cmd_opt = ft_split(av[2], ' ');
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(infile);
	ft_execve(path, cmd_opt, envp);
	ft_prterr(COM_ERR, av[2]);
}

static void ft_parent(char **path, char **av, int *fd, char **envp)
{
	char	**cmd_opt;
	int		outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
	{
		ft_double_free(path);
		ft_prterr(NO_FILE, av[4]);
	}
	cmd_opt = ft_split(av[3], ' ');
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close(fd[1]);
	close(fd[0]);
	ft_execve(path, cmd_opt, envp);
	ft_prterr(COM_ERR, av[3]);
}

static char	**ft_findpath(char **envp)
{
	char **cmd_path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
		&& envp[i][2] == 'T' && envp[i][3] == 'H')
			break;
		i++;
	}
	// printf("%s \n", envp[i]);
	cmd_path = ft_split(envp[i], ':');
	cmd_path[0] = ft_strtrim(cmd_path[0], "PATH=");
	i = 0;
	while (cmd_path[i])
	{
		cmd_path[i] = ft_strjoinfree(cmd_path[i], "/");
		i++;
	}
	return (cmd_path);
}


int main(int ac, char **av, char **envp)
{
	char **path;
	int	fd[2];
	int pid1;
	// int child_stat;
	// int err_stat;

	if (ac != 5)
		ft_prterr(ARG_ERR, NULL);
	if (pipe(fd) == -1)
		ft_prterr(PIPE_ERR, NULL);
	path = ft_findpath(envp);
	pid1 = fork();
	if (pid1 == -1)
		ft_prterr(FORK_ERR, NULL);
	if (pid1 == 0)
		ft_child(path, av, fd, envp);
	// waitpid(pid1, &child_stat, WNOHANG);
	// if (WIFEXITED(child_stat))
	// 	err_stat = WEXITSTATUS(child_stat);
	// errno = err_stat;
	// wait(NULL);
	ft_parent(path, av, fd, envp);
	//waitpid(pid1, NULL, 0);
	//waitpid(pid2, NULL, 0);
	ft_double_free(path);
	return (0);
}
