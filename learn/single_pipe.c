#include "../ft_pipex.h"

int main()
{
    int fd[2];
    int arr[] = {1, 2, 3, 4, 5, 6, 9, 4, 3};
    int sum = 0, sum_child = 0, count = sizeof(arr) / sizeof(int);
    int start, end;

    if (pipe(fd) == -1) return (1);
    int pid = fork();
    if (pid == -1) return (2);
    if (pid == 0)
        start = 0, end = count / 2;
    else
        start = count / 2, end = count;
    for (int i = start;i < end;i++)
        sum += arr[i];
    printf("The sum of arr : %d\n", sum);
    if (pid == 0)
    {
        close(fd[0]);
        printf("in the child process\n");
        usleep(2000000);
        if (write(fd[1], &sum, sizeof(sum)) == -1)
            return (3);
        close(fd[1]);
    }
    else
    {
        wait(NULL);
        printf("in the parent process\n");
        close(fd[1]);
        int sum_all;
        usleep(2000000);
        if (read(fd[0], &sum_child, sizeof(sum)) == -1)
            return (4);
        if (read(fd[0], &sum_child, sizeof(sum)) == -1)
            return (4);
        sum_all = sum + sum_child;
        close(fd[0]);
        printf("The sum of all %d\n", sum_all);
    }
    return (0);
}
