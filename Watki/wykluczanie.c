#define _XOPEN_SOURCE 500
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//zmienne globalne
int iteracje=10;
int licznik=0;
pthread_mutex_t mutex;


void* watek(void* numer_w)
{
  int nr_watku=*(int *)numer_w;
  printf("\033[%d;%dHWatek %d",nr_watku+2,1,nr_watku);
  for(int j=0;j<iteracje;j++)
  {
    printf("\033[%d;%dH\033[K\033[32mczekam\033[m\n",nr_watku+2,10);
    usleep(200000);
    pthread_mutex_lock(&mutex);
    int licznik_priv=licznik;
    licznik_priv++;
    usleep(200000);
    licznik=licznik_priv;
    printf("\033[%d;%dH\033[K",nr_watku+2,10);
    printf("\033[%d;%dH\033[31mSekcja Krytyczna(%d|%d)\033[m\n",nr_watku+2,29,j,licznik);
    usleep(300000);
    pthread_mutex_unlock(&mutex);
    printf("\033[%d;%dH\033[K\033[34m spie\033[m\n",nr_watku+2,10);
    usleep(200000);
  }
  printf("\033[%d;%dH\033[K\033[35mzakonczono\033[m\n",nr_watku+2,10);
  return numer_w;
}


int main(int argc, char *argv[])
{
  if(argc!=2)
  {
    printf("Zla liczba argumentow\n");
    exit(1);
  }
  pthread_mutex_init(&mutex,NULL);
  int watki=atoi(argv[1]);
  //tablica przechowujaca id watkow
  pthread_t thId[watki];
  //czyszcze ekran terminala
  printf("\033c");
  printf("\033[1;1HWatek Nr Sekcja prywatna    Sekcja krytyczna");
  printf("\033[%d;%dH\033[33m** Zainicjowano mutex pod adresem %p\033[m\n",watki+10,1,(void *)&mutex);
  //tworze watki
  for(int i=0;i<watki;i++)
  {
    int* numer_w=malloc(sizeof(int));
    *numer_w=i;
    int val=pthread_create(&thId[i],NULL,watek,numer_w);
    if(val!=0)
    {
      perror("pthread_create error");
      exit(1);
    }
    printf("\033[%d;%dH-- Utworzono watek o numerze %d i ID %p \n",watki+11+i,1,i,(void *)&thId[i]);
  }
  //funkcja pthread_join czeka na zakonczenie dzialania watkow
  for(int i=0; i < watki; i++)
  {
    if(pthread_join(thId[i],NULL)!=0)
    {
      perror("pthread_join error");
      exit(1);
    }
  }
//-----------------------------------------------------------------------------
//po zakonczeniu funkcji watkow

//usuniecie mutexu
  if(pthread_mutex_destroy(&mutex) !=0)
  {
    perror("pthread_mutex_destroy error");
    exit(1);
  }
//Komunikaty koncowe
  printf("\033[%d;%dH",watki+10,1);
  printf("\n** Usunieto mutex\n");
//sprawdzenie licznika
  printf("\033[%d;%dHPoprawny wynik powinien wynosic:%d\n",watki+20,1,watki*iteracje);
  printf("\033[%d;%dHWynik uzyskany:\033[32m%d\033[m\n",watki+21,1,licznik);

  if(licznik==iteracje*watki)
  {
    printf("\033[%d;%dH\033[32mWynik poprawny\033[m\n",watki+22,1);
  }
  else
  {
    printf("\033[%d;%dH\033[31mwynik niepoprawny\033[m\n",watki+22,1);
    exit(1);
  }
  exit(0);
}
