/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:04:07 by tnantaki          #+#    #+#             */
/*   Updated: 2023/02/04 20:08:52 by tnantaki         ###   ########.fr       */
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
# define HERE_DOC_PATH ".here_doc"

typedef struct s_pipe
{
	char	**path;
	char	*str_tmp;
	char	*fcmd;
	char	**cmd;
	int		here_doc;
	int		len_lim;
	int		cmd_nb;
	int		pipe_nb;
	int		*fd_pipe;
	int		fd_tmp;
	int		fd_in;
	int		fd_out;
	int		fd_read;
	int		fd_write;
	int		i;
	int		cmd_i;
	int		*pid;
	int		status;
}	t_pipe;

//setup
void	ft_check_arg(int ac, char **av, t_pipe *pipex);
void	ft_open_here_doc(char **av, t_pipe *pipex);
void	ft_open_infile(char **av, t_pipe *pipex);
void	ft_findpath(char **envp, t_pipe *pipex);
//create_pipe
void	ft_create_pipe(t_pipe *pipex);
void	ft_close_pipe(t_pipe *pipex);
//set_cmd
void	ft_first_cmd(t_pipe *pipex);
void	ft_mid_cmd(t_pipe *pipex);
void	ft_last_cmd(t_pipe *pipex, char **av);
//utils
void	ft_double_free(char **ptr);
void	ft_parent_free(t_pipe *pipex);
void	ft_fork_err(t_pipe *pipex, int errnum);
void	ft_gnl_err(t_pipe *pipex);
void	ft_prterr(int err, char *msg, int errnum);

#endif
