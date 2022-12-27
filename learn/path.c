#include <stdio.h>

int main(int ac, char **av, char **envp)
{
    int i;
    
	for(i = 0; envp[i]; i++)
		printf("index %d:%s\n", i, envp[i]);
}