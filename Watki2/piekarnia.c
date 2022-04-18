#define _XOPEN_SOURCE 500
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define THREAD 4
//wartosci ustawione wszedzie na 0
// zakladam ze 0-false a 1-true
volatile int wybieranie[THREAD];
volatile int numer[THREAD];
int max;
int licznik=0;
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
void* watek(void* numer)
{
  int nr_watek=*(int *)numer;
  printf("\033[%d;%dH",nr_watek+2,1);
  printf("Watek %d ",nr_watek);

  for(int j=0;j<10;j++)
  {
    printf("\033[%d;%dH\033[K\033[32mczekam\033[m\n",nr_watek+2,10);
    usleep(200000);
    lock(nr_watek);
    //sekcja krytyczna
    usleep(200000);
    licznik=licznik+1;
    printf("\033[%d;%dH\033[K",nr_watek+2,10);
    printf("\033[%d;%dH\033[31mSekcja Krytyczna(%d|%d)\033[m\n",nr_watek+2,29,j,licznik);
    usleep(200000);
    unlock(nr_watek);
    printf("\033[%d;%dH\033[K\033[34m spie\033[m\n",nr_watek+2,10);
    usleep(200000);
  }
  printf("\033[%d;%dH\033[K\033[35mzakonczono\033[m\n",nr_watek+2,10);
  return numer;
}




int main(void)
{
  pthread_t thId[THREAD];
  printf("\033c");
  printf("\033[1;1HWatek Nr Sekcja prywatna    Sekcja krytyczna");
  for(int i=0;i<THREAD;i++)
  {
    int* number_th=malloc(sizeof(int));
    *number_th=i;
    int id=pthread_create(&thId[i],NULL,&watek,number_th);
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
  //Komunikaty koncowe
  //sprawdzenie licznika
    printf("\033[%d;%dHPoprawny wynik powinien wynosic:%d\n",THREAD+10,1,THREAD*10);
    printf("\033[%d;%dHWynik uzyskany:\033[32m%d\033[m\n",THREAD+11,1,licznik);

    if(licznik==10*THREAD)
    {
      printf("\033[%d;%dH\033[32mWynik poprawny\033[m\n",THREAD+12,1);
    }
    else
    {
      printf("\033[%d;%dH\033[31mwynik niepoprawny\033[m\n",THREAD+12,1);
      exit(1);
    }
  exit(0);
}
