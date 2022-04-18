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
  //we want to create a situation when the parent process will end before child process
  else if(value>0)
  {
      sleep(1);
      exit(0);
  }
  // we use a long sleep to find which process adopts our orphan process.
  else if (value==0)
  {
    sleep(50);
    exit(0);
  }
}
