#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
int status;
void potomek(char* option,char* signall)
{
  switch(fork())
  {
    case -1:
            perror("fork error");
            exit(1);
    case 0:
            if((execl("obsluga.x","obsluga.x",option,signall,NULL))==-1)
            {
              perror("exec error");
              exit(1);
            }
            break;
  }
}

int main(int argc, char* argv[])
{
  if(argc!=3)
  {
    perror("Wrong number of arguments");
    exit(1);
  }
  char *option = argv[1];
  int nr_syg  = atoi(argv[2]);
  char *signall=argv[2];
  int pid=fork();
  switch(pid)
  {
    case -1:
            perror("fork error");
            exit(1);
    case 0:
            setpgid(getpid(),0); //stal sie liderem grupy

            if(signal(nr_syg,SIG_IGN)==SIG_ERR)
            {
              perror("ignore operation failed\n");
              exit(1);
            }

            for(int i=0;i<3;i++)
            {
              potomek(option,signall);
            }
            
            for(int j=0;j<3;j++)
            {
              wait(&status);
              printf("Status:%d\n",status);
            }
            break;
     default:
              sleep(1);
              //checking if the group exist
             if(kill(-(getpgid(pid)),0)==-1)
              {
                perror("Group error");
                exit(1);
              }
              //sending signal to gruop of the lider process
              if(kill(-(getpgid(pid)),nr_syg))
              {
                perror("Group error");
                exit(1);
              }
              if(wait(NULL)==-1)
              {
                perror("fork error");
                exit(1);
              }
              break;
  }
exit(0);
}
