#include <stdio.h>
#include <signal.h>

int main() {
    printf("\n\tProgram terminated by user\n");
  raise(SIGINT);

  return 0;
}