#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int	child(char *str)
{
	sleep (4);
	exit (2);
}

int	main(void)
{
	int	pid = fork();
	int	status;

	if (pid == 0)
		child("Hello");
	waitpid(pid, &status, 0);
	printf("Parent\n");
	printf("status:%d\n", WEXITSTATUS(status));
}
