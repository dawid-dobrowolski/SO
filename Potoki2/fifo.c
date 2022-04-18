#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
// Rights Access - 0666 means that everbody has read and write access
#define RIGHTS 0666
// global variable which holds the name of pipe
const char* function;
// own signal handling
void my_sighandler()
{
  printf("\nUsuwam potok na zadanie sygnalu SYGINT\n");
  if(unlink(function)==-1)
  {
    perror("unlink error");
    exit(1);
  }
  _exit(1);
}
//function called by atexit which remove pipe by unlink()
void koniec(void)
{
  if(unlink(function)==-1)
  {
    perror("unlink error");
    exit(1);
  }
}
int main(int argc,char* argv[])
{
    if(atexit(koniec)!=0)
    {
      perror("atexit error:");
      _exit(1);
    }
    int c=2;
    if(argc != 4)
      {
        printf("%s",argv[0]);
        _exit(1);
      }
    //creating a pipe
    const char* name=argv[3];
    function=name;
    if(mkfifo(name,RIGHTS)==-1)
    {
      perror("mkfifo error");
      _exit(1);
    }
    switch(fork())
    {
      case -1:
            perror("fork error");
            exit(1);
      case  0:
            if(execl("./producent.x","producent.x",argv[1],argv[2],argv[3],NULL)==-1)
            {
              perror("execl error");
              _exit(1);
            }
            break;
    }
    switch(fork())
    {
      case -1:
            perror("fork error");
            exit(1);
      case  0:
            if(execl("./konsument.x","konsument.x",argv[1],argv[2],argv[3],NULL)==-1)
            {
              perror("execl error");
              _exit(1);
            }
            break;
    }
   if(signal(SIGINT,my_sighandler)==SIG_ERR)
    {
      perror("signal error");
      exit(1);
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
exit(0);
}
