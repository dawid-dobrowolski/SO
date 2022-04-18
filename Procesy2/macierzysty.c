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

  int f_numbers=3; // loop limit
  int c=0; // child counter

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
          // execv takes arrays of arguments
          char* arg[] = { "./potomny.x",NULL };
          // execv initiates a new process from the indicated program
          execv("./potomny.x",arg);
          break;

       default:
          c++;
          break;
    }
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
