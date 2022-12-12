#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
	int fd[2];
	pipe(fd);
	int pid = fork();
	int i = 4;
	if (pid == 0)
	{
		int x;
		read(fd[0], &x, sizeof(x));
		printf("first read  : %d\n", x);
		x *= 2;
		write(fd[1], &x, sizeof(x));
		printf("second write: %d\n", x);
		usleep(1000000);
		read(fd[0], &x, sizeof(x));
		printf("Third read  : %d\n", x);
		x *= 2;
		write(fd[1], &x, sizeof(x));
		printf("fourth write: %d\n", x);
		usleep(1000000);
		// usleep(1000000);
		// printf("Sending Value %d\n", x);
		// printf("child fd[0]:%d\n", fd[0]);
		// printf("child fd[1]:%d\n", fd[1]);
	}
	else
	{
		int j = 3;
		write(fd[1], &j, sizeof(j));
		printf("first write : %d\n", j);
		usleep(1000000);
		read(fd[0], &j, sizeof(j));
		printf("second read : %d\n", j);
		j *= 3;
		write(fd[1], &j, sizeof(j));
		printf("Third write : %d\n", j);
		usleep(1000000);
		read(fd[0], &j, sizeof(j));
		printf("fourth read : %d\n", j);
		// printf("Get Value %d\n", j);
		// printf("parent fd[0]:%d\n", fd[0]);
		// printf("parent fd[1]:%d\n", fd[1]);
	}
	close(fd[0]);
	close(fd[1]);
}
