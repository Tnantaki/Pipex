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
int child_process(int *fd, av)

int main(int ac, char **av, char **envp)
{
	int pid;
	int fd_in[2];
	int ft_out[2];
	if (pipe(fd_in) == -1)
		exit (1);
	if (pipe(fd_out) == -1)
		exit (1);
	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
		child_process(fd, )
}
