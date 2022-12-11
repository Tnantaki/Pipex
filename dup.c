#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main(void)
{
	int pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		while (1)
		{
			printf("We are in the Child process\n");
			sleep(1);
		}
	}
	else
	{
		printf("pid == :%d\n", pid);
		sleep(5);
		kill(0, SIGKILL);
		printf("Hello\n");
		wait(NULL);
	}
}
