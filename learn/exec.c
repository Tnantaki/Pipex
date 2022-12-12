#include "../ft_pipex.h"

int main(void)
{
	int fd[2];
	if (pipe(fd) == -1) return (1);
	int pid = fork();
	if (pid == -1) return (1);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		execlp("ls", "ls", "-la", ".", NULL);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execlp("grep", "grep", "file", NULL);
	}
	close(fd[1]);
	close(fd[0]);
	wait(NULL);
	printf("Hello\n");
}
