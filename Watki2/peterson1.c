#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Zaimplementować algorytm Petersona do wzajemnego
//wykluczania DWÓCH wątków, z i bez użycia muteksów biblioteki POSIX,
// oraz zademonstrować jego działanie.
int licznik=0;
volatile int kolej=0;
volatile int flaga[2];
//-------------------------------------------------------------------------------
void lock(int nr_watek)
{
  flaga[nr_watek]=1;
  kolej = 1- nr_watek;
  __sync_synchronize();
  while(flaga[1-nr_watek] && kolej == 1-nr_watek);
}
//-------------------------------------------------------------------------------
void unlock(int nr_watek)
{
  flaga[nr_watek]=0;
  __sync_synchronize();
}
//-------------------------------------------------------------------------------
void* watek(void* numer)
{
  int nr_watek=*(int *)numer;
  for(int i=0;i<1000;i++)
  {
    lock(nr_watek);
    licznik=licznik+1;
    unlock(nr_watek);
  }
  return numer;
}

int main(void)
{
  pthread_t thId[2];
  for(int i=0;i<2;i++)
  {
    int* numer_w=malloc(sizeof(int));
    int val=pthread_create(&thId[i],NULL,watek,numer_w);
    if(val!=0)
    {
      perror("pthread_create error");
      exit(1);
    }
  }
  //funkcja pthread_join czeka na zakonczenie dzialania watkow
  for(int i=0; i < 2; i++)
  {
    if(pthread_join(thId[i],NULL)!=0)
    {
      perror("pthread_join error");
      exit(1);
    }
  }
  printf("Licznik ma wartosc: %d\n",licznik);
  exit(0);
}
