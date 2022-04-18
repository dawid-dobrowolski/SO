#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>



int main(int argc, char* argv[])
{
    if(argc!=3)
    {
      perror("Wrong number of arguments");
      exit(1);
    }
    int nr_syg  = atoi(argv[2]);
    int pid=fork();
    switch(pid)
    {
      case -1:
          perror("fork error");
          exit(1);

       case 0:
          if((execl("./obsluga.x","obsluga.x",argv[1],argv[2],NULL))==-1)
          {
            perror("exec error");
            exit(1);
          }
          break;
       default:
          //checking if the child process exist
          if(kill(pid,0)==-1)
          {
            perror("kill error");
            exit(1);
          }
          sleep(2);
          //sending signal to child
          if(kill(pid,nr_syg)==-1)
          {
            perror("kill error");
            exit(1);
          }
          break;
    }
    exit(0);
  }
