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
		ft_putstr_fd("Invalid number of argument.\n", STDERR_FILENO);
	else if (err == 2)
		perror("Pipe error :");
	else if (err == 3)
		perror("Fork error :");
	else if (err == 4)
		msg = ft_strjoin(msg, ": no such file or directory\n");
	else if (err == 5)
		msg = ft_strjoin(msg, ": no such file or directory\n");
	else if (err == 6)
		msg = ft_strjoinfree(msg, ": command not found\n");
	if (msg && (err == 4 || err == 5 || err == 6))
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
	}
	exit (errnum);
}

// void	ft_prterr(int err, char *msg, int errnum)
// {
// 	if (err == 1)
// 		ft_putstr_fd("Program take only 4 arguments.\n", STDERR_FILENO);
// 	else if (err == 2)
// 		perror("Pipe error :");
// 	else if (err == 3)
// 		perror("Fork error :");
// 	else if (err == 4)
// 	{
// 		// ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
// 		// ft_putendl_fd(msg, STDERR_FILENO);
// 	}
// 	else if (err == 5)
// 	{
// 		// ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
// 		// ft_put2endl_fd(msg, STDERR_FILENO);
// 	}
// 	else if (err == 6)
// 	{
// 		// ft_putstr_fd("zsh: command not found: ", STDERR_FILENO);
// 		// ft_putendl_fd(msg, STDERR_FILENO);
// 	}
// 	exit (errnum);
// }
