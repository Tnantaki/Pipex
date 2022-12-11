#include <unistd.h>

int main(void) {
  char *programName = "ls";
  char *arg1 = "-la";

  execlp(programName, arg1, NULL);

  return 0;
}
