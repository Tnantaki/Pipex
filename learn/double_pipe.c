#include "../ft_pipex.h"

int main(void)
{
	int fd1[2]; // C => P
	int fd2[2]; // P => C
	if (pipe(fd1) == -1) exit(1);
	if (pipe(fd2) == -1) exit(1);
	int pid = fork();
	if (pid == -1) exit(2);
	if (pid == 0)
	{ // Child Process
		close(fd2[1]);
		close(fd1[0]);
		int x;
		usleep(2000000);
		if (read(fd2[0], &x, sizeof(x)) == -1) exit (3);
		printf("the recieved : %d\n", x);
		x *= 2;
		usleep(2000000);
		if (write(fd1[1], &x, sizeof(x)) == -1) exit (3);
		printf("Wrote : %d\n", x);
		close(fd2[0]);
		close(fd1[1]);
	}
	else
	{ // Paretn Process
		close(fd2[0]);
		close(fd1[1]);
		srand(time(NULL));
		int t = rand()%10;
		if (write(fd2[1], &t, sizeof(t)) == -1) exit (4);
		printf("Wrote %d\n", t);
		usleep(2000000);
		if (read(fd1[0], &t, sizeof(t)) == -1) exit (5);
		usleep(2000000);
		printf("the result : %d\n", t);
		close(fd2[1]);
		close(fd1[0]);
	}
}
