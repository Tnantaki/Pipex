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
	ptr = NULL;
}

void	ft_prterr(int err, char *msg)
{
    if (err == 1)
	{
	    ft_putstr_fd("Program take only 4 arguments.\n", STDERR_FILENO);
		exit (1);
	}
	else if (err == 2)
		perror("Pipe error :");
	else if (err == 3)
		perror("Fork error :");
    else if (err == 4)
	{
		ft_putstr_fd("-bash: ", STDERR_FILENO);
		perror(msg);
	}
    else if (err == 5)
	{
	    ft_putstr_fd(msg , STDERR_FILENO);
	    ft_putstr_fd(": Command not found\n", STDERR_FILENO);
	}
	exit (errno);
}