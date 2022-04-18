#define _DEFAULT_SOURCE
#include  <stdio.h>
#include  <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include "sem.h"
sem_t *sem;
int value;
const char* name="/semafor_powielacz";
int main(int argc, char* argv[])
{
  int seconds=(rand()%4+1);
  semOpen(name);
  FILE *fread;
  int liczba,critic,semval;
  critic=atoi(argv[2]);

  for(int i=0;i<critic;i++)
  {

    int pid=getpid();
    if((semval=(sem_getvalue(sem,&value)))==-1)
    {
      perror("semInfo error");
      exit(1);
    }
    printf("***Przed sekcja krytyczna| PID: %d |Wartosc semafora:%d  |Liczba sekcji krytycznych: %d\n",pid,value,i+1);
    printf("\t");
    usleep(seconds);
    semP(sem);

    if((fread=fopen("numerki.txt","r"))==NULL)
    {
    perror("fopen error");
    exit(1);
    }
    if(fscanf(fread, "%d",&liczba)!=EOF)
    {}
    fclose(fread);
    if((semval=(sem_getvalue(sem,&value)))==-1)
    {
      perror("semInfo error");
      exit(1);
    }
    printf("\t***W sekcji krytycznej| PID: %d |Wartosc semafora:%d  |Liczba sekcji krytycznych: %d\n",pid,value,i+1);
    usleep(seconds);
    FILE *fwrite=fopen("numerki.txt","w");
    if(!fwrite)
    {
      perror("fopen error");
      exit(1);
    }
    usleep(seconds);
    liczba=liczba+1;
    fprintf(fwrite,"%d",liczba);
    fclose(fwrite);
    printf("\t");
    semV(sem);
    if((semval=(sem_getvalue(sem,&value)))==-1)
    {
      perror("semInfo error");
      exit(1);
    }
    printf("***Po sekcji krytycznej| PID: %d |Wartosc semafora:%d  |Liczba sekcji krytycznych: %d\n\n",pid,value,i+1);
  }
exit(0);
}
