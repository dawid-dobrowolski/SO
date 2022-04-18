#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "procinfo.h"
extern const char * const sys_siglist[]; //

void my_sighandler(int nr_syg)
{
  printf("Numer otrzymanego sygnalu : %d\n",nr_syg);
}

int main(int argc, char* argv[])
{
  //checking if the number of arguments is correct
  if(argc!=3)
  {
    perror("Wrong number of arguments");
    exit(1);
  }
  procinfo(argv[0]);
  // convert single char to int value in ASCII
  int choice=(int)*argv[1];
  // convert string to int using atoi function
  int nr_syg  = atoi(argv[2]);

  switch(choice)
  {
    case 100:
              if(signal(nr_syg,SIG_DFL)==SIG_ERR)
              {
                perror("default operation failed");
                exit(1);
              }
              break;
    case 105:
              if(signal(nr_syg,SIG_IGN)==SIG_ERR)
              {
                perror("ignore operation failed");
                exit(1);
              }
              break;
    case 112:
              if(signal(nr_syg,my_sighandler)==SIG_ERR)
              {
                perror("Error");
                exit(1);
              }
              break;
    default:
              perror("Misuse of the program");
              exit(1);
  }

  printf("obsluga.x:Waiting for a signal\n");
  pause();
  exit(0);
}
