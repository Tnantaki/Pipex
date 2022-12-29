# ifndef PIPEX_H
#define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

# include <signal.h>

# define ARG_ERR 1
# define PIPE_ERR 2
# define FORK_ERR 3
# define NO_FILE 4
# define COM_ERR 5

//utils
void	ft_double_free(char **ptr);
void	ft_prterr(int err, char *msg);

#endif
