#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	char *str = "Hello";
	int i = 0;
	int pid;
	while (i++ < 1)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("I'm Child, pid:%d\n", pid);
			usleep(5000000);
			pid = fork();
			if (pid == 0)
				printf("I'm Child, pid:%d\n", pid);
			else
				printf("I'm Parent, pid:%d\n", pid);
		}
		else
		{
			printf("I'm Grandparent, pid:%d\n", pid);
			wait(NULL);
		}
	}
	return (0);
}
