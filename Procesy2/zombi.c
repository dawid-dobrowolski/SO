//=================================================================================
// Author: Dawid Dobrowolski SO Group 7,
//=================================================================================
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
  int value;
  value=fork();

  //error control
  if(value<0)
  {
    perror("Fork error:");
    exit(1);
  }

  // we want the parent process to continue running when the child process is completed
  // to see that the child process is now a zombii process
  if(value>0)
  {
    sleep(20);
  }
  else if(value==0)
  {
    exit(0);
  }
  return 0;
}
