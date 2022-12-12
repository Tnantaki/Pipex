#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int n;
	int pid = fork();
	// fork();
	if (pid == 0)
		sleep(1);
	else
	{
		n = 6;
		// wait(NULL);
	}
	if (pid == 0)
	{
		printf("I'm Child  PID:%d, PPID:%d\n", getpid(), getppid());
	}
	else
		printf("I'm Parent PID:%d, PPID:%d\n", getpid(), getppid());
}
