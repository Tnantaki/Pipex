#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    // int fd = open("file1.txt", O_WRONLY);
    // dup2(fd, 1);
    close(STDOUT_FILENO);
    printf("I will leave this message\n");
}