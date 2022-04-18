#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"
sem_t *sem;
int main(int argc,char* argv[])
{
  int value=1;
  const char *name="/semaforproba";
  printf("-----Test Biblioteki-------\n");
  printf("-----1.Utworzenie semafora-------\n");
  sleep(1);
  semCreate(name,value);
  sleep(1);
  printf("-----2.Dostep do juz istniejacego semafora-------\n");
  semOpen(name);
  sleep(1);
  printf("-----3.Info o wartości semafora-------\n");
  semInfo(sem);
  sleep(1);
  printf("-----4.Opuszczenie semaforu\n");
  semP(sem);
  semInfo(sem);
  sleep(1);
  printf("-----5.Podniesienie semaforu\n");
  semV(sem);
  semInfo(sem);
  sleep(1);
  printf("-----6.Usuniecie semafora-------\n");
  semRemove(name);
  semClose(sem);
  exit(0);
}
