#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	// int fd = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0777);
	// printf("fd:%d\n", fd);
	// unlink("outfile");
	// printf("fd:%d\n", fd);
	// write(fd, "hello\n", 6);
	// int fd2 = open("infile", O_RDWR);
	// printf("fd:%d\n", fd2);
	int pid = fork();
	if (pid == 0)
	{
		sleep (4);
		printf("Child\n");
	}
	else
	{
		wait(NULL);
		// execve();
		sleep (5);
		printf("Parent\n");
	}
	// wait(NULL);
}
