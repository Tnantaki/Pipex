#include "../ft_pipex.h"

int main(void)
{
	int fd[2];
	if (pipe(fd)) return(2);
	int pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		close(fd[0]);
		int nb[10];
		for (int i = 0; i < 10; i++)
			nb[i] = (2 * i) % 10;
		write(fd[1], nb, sizeof(int) * 10);
	}
	else
	{
		close(fd[1]);
		int b[10];
		usleep(5000);
		read(fd[0], b, sizeof(int) * 10);
		for (int j = 0; j < 10; j++)
			printf("%d, ", b[j]);
		printf("\n");
		wait(NULL);
	}
}
