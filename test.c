#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void    process(int n)
{
    int now;
    int end;

    now = 0;
    end = 3;
    while (now < end)
    {
        printf("n :%d %d < %d\n",n ,now, end);
        usleep(500000);
        now++;
    }
}


int main(void)
{
    int i = -1;
    pid_t pid;
    while (++i < 3)
    {
        pid = fork();
        printf("pid: %d\n",pid);
        if (pid < 0)
            return (1);
        else if (pid == 0)
        {
            process(i);
            return (0);
        }
    }

    i = -1;
    while (++i < 1)
    {
        printf("waiting\n");
        printf("pid end >%d\n", waitpid(-1, NULL, 0));
    }
    printf("program done\n");
    return (0);
}
