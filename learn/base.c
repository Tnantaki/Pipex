#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include <unistd.h>
 
int main(int a, char **b, char **c) 
{
  char *binaryPath = "/bin/bash";
  char *const args[] = {binaryPath, "-c", "echo ", "Visit $HOSTNAME:$PORT from your browser.", NULL};
  char *const env[] = {"HOSTNAME=www.linuxhint.com", "PORT=8080", NULL};
  execve(binaryPath, args, env);
  return 0;
}
