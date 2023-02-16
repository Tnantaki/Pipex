/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:04:07 by tnantaki          #+#    #+#             */
/*   Updated: 2023/02/05 00:22:03 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

# define ARG_ERR 1
# define PIPE_ERR 2
# define FORK_ERR 3
# define NO_INFILE 4
# define NO_OUTFILE 5
# define COM_ERR 6

typedef struct s_pipe
{
	char	**path;
	int		fd_pipe[2];
	int		pid1;
	int		pid2;
	int		status;
}	t_pipe;

//utils
void	ft_double_free(char **ptr);
void	ft_prterr(int err, char *msg, int errnum);

#endif
