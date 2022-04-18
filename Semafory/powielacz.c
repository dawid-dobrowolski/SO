#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "sem.h"

const char* name="/semafor_powielacz";
sem_t *sem;
void my_sighandler()
{
  printf("\nUsuwam semafor na zadanie sygnalu SYGINT\n");
  semRemove(name);
  _exit(1);
}

void koniec(void)
{
  semRemove(name);
}

int main(int argc, char* argv[])
{
  if(argc!=4)
  {
    perror("Wrong number of arguments");
    exit(1);
  }
  if(atexit(koniec)!=0)
  {
    perror("atexit error:");
    _exit(1);
  }
  if(signal(SIGINT,my_sighandler)==SIG_ERR)
   {
     perror("signal error");
     exit(1);
   }
   FILE *fwrite=fopen("numerki.txt","w");
   if(!fwrite)
   {
     perror("fopen error");
     exit(1);
   }
   int liczba=0;
   fprintf(fwrite,"%d",liczba);
   fclose(fwrite);

  int value=1;
  semCreate(name,value);
  semOpen(name);
  printf("\n PID=%d|Nazwa semafora:%s|Adres %p\n\n",getpid(),name,(void *)sem);
  int number=atoi(argv[2]);
  int check=atoi(argv[3]);
  sleep(1);
  for(int i=0;i<number;i++)
  {
    switch(fork())
    {
      case -1:
              perror("fork error");
              _exit(1);
      case 0:

              if((execl(argv[1],"prog.x",argv[2],argv[3],NULL))==-1)
              {
                perror("exec error");
                _exit(1);
              }
              break;
      default:
              break;
    }
  }
  for(int j=0;j<number;j++)
  {
    if(wait(NULL)==-1)
    {
      perror("fork error");
      exit(1);
    }
  }
    FILE *fread;
    if((fread=fopen("numerki.txt","r"))==NULL) // otwieram plik z definicja read
    {
    perror("fopen error");
    exit(1);
    }
    if(fscanf(fread, "%d",&liczba)!=EOF)
    {
    }
    fclose(fread);
    if(liczba!=number*check)
    {
      printf("SPRAWDZENIE:Bledna liczba koncowa\n");
    }
    else
    {
      printf("SPRAWDZENIE:Numer poprawny\n");
    }
  exit(0);
}
