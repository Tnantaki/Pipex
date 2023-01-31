/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:46:07 by tnantaki          #+#    #+#             */
/*   Updated: 2023/01/30 23:46:12 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_double_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free (ptr[i]);
		i++;
	}
	free (ptr);
}

void	ft_prterr(int err, char *msg, int errnum)
{
	if (err == 1)
		ft_putstr_fd("Program take only 4 arguments.\n", STDERR_FILENO);
	else if (err == 2)
		perror("Pipe error :");
	else if (err == 3)
		perror("Fork error :");
	else if (err == 4)
	{
		ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	else if (err == 5)
	{
		ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	else if (err == 6)
	{
		ft_putstr_fd("zsh: command not found: ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	exit (errnum);
}

char	*ft_fcmd(char **path, char **cmd, char *av)
{
	char	*fcmd;
	int		i;

	i = 0;
	if (access(cmd[0], F_OK) == 0)
		return (ft_double_free(path), fcmd = ft_strjoin("", cmd[0]));
	if (strncmp(cmd[0], "/bin", 4) == 0 && access(cmd[0], F_OK) != 0)
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
