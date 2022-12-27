#include "../ft_pipex.h"

int main(void)
{
	int tube[2];
	pipe(tube);
	printf("fd[0]:%d\n", tube[0]);
	printf("fd[1]:%d\n", tube[1]);
	int fd1 = open("file1.txt", O_RDWR);
	int fd2 = open("file2.txt", O_RDWR);
	printf("fd1:%d\n", fd1);
	printf("fd2:%d\n", fd2);
	dup2(fd1, fd2);
	write(fd2, "Hello\n", 6);
	write(fd1, "World\n", 6);
	// write(1, "Hello\n", 6);
	// int newfd = dup(1);
	// printf("newfd:%d\n", newfd);
	// write(5, "Hello\n", 6);
	// int rd = open("file2.txt", O_WRONLY);
	// printf("rd:%d\n", rd);
	// dup2(rd, 1);
	// write(1, str, 15);
}
