#include "../ft_pipex.h"

int main(int a,char **b, char **c)
{
    int i  = 0;
    for(int i=0; c[i]; i++)
        printf("envp[%d] : %s\n", i, c[i]);
}
