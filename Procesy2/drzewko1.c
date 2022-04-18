//=================================================================================
// Author: Dawid Dobrowolski SO Group 7,
//=================================================================================
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "procinfo.h"

int main(int argc, char* argv[])
{
  procinfo(argv[0]);

  int f_numbers=3;
  int c=0;

  for(int i=0; i<f_numbers; i++)
  {

    switch(fork())
    {

      case -1:
          perror("fork error");
          exit(1);

       case 0:
          c=0;
          sleep(1);
          printf("  Proces potomny : UID: %d, GIT: %d, PID: %d, PPID: %d, PGID: %d \n",getuid(),getgid(),getpid(),getppid(),getpgrp());
          break;

       default:
          c++;
          break;
    }
    if(c==0)break;
  }
  while(c>0)
  {
    if(wait(NULL)==-1)
    {
      perror("fork error");
      exit(1);
    }
    c--;
  }
  return 0;
}
