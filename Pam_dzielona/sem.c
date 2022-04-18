#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include "sem.h"
semid sem;
//  Tworzy semafor z wartością początkową val
semid semCreate(const char *name, int val)
{
  sem = sem_open(name, O_CREAT | O_EXCL, 0666,val);
  if(sem == SEM_FAILED)
  {
    perror("semCreate error");
    exit(1);
  }
  printf("Utworzony zostal semafor z wartoscia: %d\n",val);
  return sem;
}

//  Usuwa semafor
void semRemove(const char *name)
{
  if(sem_unlink(name)==-1)
  {
    perror("semRemove error");
    exit(1);
  }
  printf("Usuniety zostal semafor o nazwie: %s\n",name);
}

//  Uzyskuje dostęp do istniejącego semafora
semid semOpen(const char *name)
{
  sem = sem_open(name,O_EXCL);
  if(sem == SEM_FAILED)
  {
    perror("semOpen error");
    exit(1);
  }
  printf("Uzyskano dostep do istniejacego semafora o nazwie: %s\n",name);
  return sem;
}
//  Zamyka semafor w danym procesie
void semClose(semid sem)
{
  if(sem_close(sem)==-1)
  {
    perror("semClose error");
    exit(1);
  }
  printf("Zamknieto semafor\n");
}

//  Opuszcza semafor: zmniejsza wartość semafora o 1 lub czeka
void semP(semid sem)
{
  if(sem_wait(sem)==-1)
  {
    perror("semP error");
    exit(1);
  }
  printf("Opuszczenie semfaoru\n");
}
//  Podnosi semafor: zwiększa wartość semafora o 1 lub wznawia czekający proces
void semV(semid sem)
{

  if(sem_post(sem)==-1)
  {
    perror("semV error");
    exit(1);
  }
  printf("Podniesienie semaforu\n");
}

//  Funkcja wypisuje informację o wartości semafora
void semInfo(semid sem)
{
  int value;
  if(sem_getvalue(sem,&value)==-1)
  {
    perror("semInfo error");
    exit(1);
  }
  printf("Wartosc semafora: %d\n",value);
}
