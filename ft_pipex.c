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

#include "ft_pipex.h"

static void ft_child1(char **cmd_path, char **av, int *fd)
{
	char	**cmd_opt;
	char 	*cmd;
	int		infile;
	int	i;

	i = 0;
	infile = open (av[1], O_RDONLY);
	cmd_opt = ft_split(av[2], ' ');
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(infile);
	while (cmd_path[i])
	{
		cmd = ft_strjoin(cmd_path[i], cmd_opt[0]);
		if (access(cmd, F_OK) == 0)
			execve(cmd, cmd_opt, NULL);
		free (cmd);
		i++;
	}
}

static void ft_child2(char **cmd_path, char **av, int *fd)
{
	char	**cmd_opt;
	char	*cmd;
	int		outfile;
	int	i;

	i = 0;
	outfile = open (av[4], O_WRONLY);
	cmd_opt = ft_split(av[3], ' ');
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close(fd[1]);
	close(fd[0]);
	while (cmd_path[i])
	{
		cmd = ft_strjoin(cmd_path[i], cmd_opt[0]);
		if (access(cmd, F_OK) == 0)
			execve(cmd, cmd_opt, NULL);
		free (cmd);
		i++;
	}
}

char	**ft_findpath(char **envp)
{
	char **cmd_path;
	int i = 0;

	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
			break;
		i++;
	}
	cmd_path = ft_split(envp[i], ':');
	cmd_path[0] = ft_strtrim(cmd_path[0], "PATH=");
	i = 0;
	while (cmd_path[i])
	{
		cmd_path[i] = ft_strjoin(cmd_path[i], "/");
		i++;
	}
	return (cmd_path);
}

void	ft_ptrerr(int errnb)
{
	if (errnb == 1)
		ft_putstr_fd(ARG_ERR, STDOUT_FILENO);
}

int main(int ac, char **av, char **envp)
{
	char **cmd_path;
	int	fd[2];
	int pid1;
	int pid2;

	if (ac != 5)
		ft_ptrerr(1);
	cmd_path = ft_findpath(envp);
	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
		ft_child1(cmd_path, av, fd);
	pid2 = fork();
	if (pid2 == 0)
		ft_child2(cmd_path, av, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
