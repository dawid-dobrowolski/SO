#define _XOPEN_SOURCE 500
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define THREAD  4
#define LOOP  10000
//wartosci ustawione wszedzie na 0
// zakladam ze 0-false a 1-true
volatile int wybieranie[THREAD];
volatile int numer[THREAD];
int max;
volatile int licznik = 0; // Globalny licznik
//-------------------------------------------------------------------------------
//lock function
void lock(int nr_watek)
{
  wybieranie[nr_watek]=1;

  for(int n=0;n<THREAD;n++)
  {
    int liczba=numer[n];
    if(liczba>max)
    {
      max=liczba;
    }
  }
  numer[nr_watek]=max+1;

  __sync_synchronize();
  wybieranie[nr_watek]=0;
  __sync_synchronize();
  for(int j=0;j<THREAD;j++)
  {
    while(wybieranie[j]);
    while(numer[j] !=0 && (numer[j] < numer[nr_watek] || (numer[j] == numer[nr_watek] && j < nr_watek)));


  }
}
//-------------------------------------------------------------------------------
//unlock function
void unlock(int nr_watek)
{
  __sync_synchronize();
  numer[nr_watek]=0;
}
//-------------------------------------------------------------------------------
//funkcja watku
void* watek(void* number)
{
  int nr_watek=*(int *)number;
  for(int i = 0; i<LOOP;i++)
  {

    lock(nr_watek);

    licznik=licznik+1;

    unlock(nr_watek);
  }

  return number;
}
//--------------------------------------------------------------------------------



int main(void)
{

  pthread_t thId[THREAD];
  for(int i=0;i<THREAD;i++)
  {
    int* number=malloc(sizeof(int));
    *number=i;
    int id=pthread_create(&thId[i],NULL,&watek,number);
    if(id!=0)
    {
      perror("pthread_create error");
      exit(1);
    }
  }

  for(int i=0; i < THREAD; i++)
  {
    if(pthread_join(thId[i],NULL)!=0)
    {
      perror("pthread_join error");
      exit(1);
    }
  }
  printf("Wartosc licznika:%d\n",licznik);
  exit(0);
}
