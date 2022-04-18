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
  //Call function procinfo for parent process
  procinfo(argv[0]);

  int f_numbers=3;

  for(int i=0; i<f_numbers; i++)
  {
    switch(fork())
    {

      case -1:
          perror("fork error");
          exit(1);

       case 0:
          printf("  Proces potomny : UID: %d, GIT: %d, PID: %d, PPID: %d, PGID: %d \n",getuid(),getgid(),getpid(),getppid(),getpgrp());
          sleep(1);
          break;
       default:
          //that allows us to list all 1 genereation child processes first
          //when i==f_numbers-1 then all process start waiting for their child processes
          if(i==f_numbers-1)
          {
            wait(NULL);
            sleep(1);
          }
          break;
    }
  }
  sleep(1);
  return 0;
}
