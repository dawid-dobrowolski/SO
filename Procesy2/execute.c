//=================================================================================
// Author: Dawid Dobrowolski SO Group 7,
//=================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  printf("pierwszy komunikat\n");
  execl("./potomny.x","potomny.x",NULL);
  printf("drugi komunikat");
  return 0;
}
