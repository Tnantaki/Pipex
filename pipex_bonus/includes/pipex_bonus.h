/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:04:07 by tnantaki          #+#    #+#             */
/*   Updated: 2023/02/02 18:22:23 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
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
# define HERE_DOC 7

typedef struct s_pipe
{
	char	**path;
	char	*tmp;
	int		*fd_pipe;
	int		here_doc;
	int		len;
	int		cmd_nb;
	int		pipe_nb;
	int		fd_in;
	int		pid;
	int		pid1;
	int		pid2;
	int		status;
}	t_pipe;

//utils
void	ft_double_free(char **ptr);
void	ft_prterr(int err, char *msg, int errnum);
char	*ft_fcmd(char **path, char **cmd, char *av);
//create_pipe
void	ft_create_pipe(t_pipe *pipex);
void	ft_close_pipe(t_pipe pipex);

#endif
