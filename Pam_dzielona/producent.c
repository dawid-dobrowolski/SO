#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include "shmem.h"
#include "sem.h"
#define NELE 5
#define NBUF 5


sem_t *sm1;
sem_t *sm2;
const char* sem1="/semafor_1";
const char* sem2="/semafor_2";

const char* memoryname="/shared_memory";
const int size_shm=1024;
int fd;
int file_r,produkcja,data;
char producent;
char koniec=';';
int main(int argc,char* argv[])
{
  typedef struct
  {
    int  size;
    int  tail;
    int  head;
    char buf[NELE];
  }Towar;
  //Otwieram i wypisuje komunikaty
  sm1=semOpen(sem1);
  printf("SEM1|");semInfo(sm1);
  sm2=semOpen(sem2);
  printf("SEM2|");semInfo(sm2);
  fd=shmOpen(memoryname);
  shmInfo(fd);
  sleep(1);
  //odwzorowuje
  Towar *wpd=(Towar *)mmap(NULL,sizeof(Towar),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  //otwieram plik z którego będę czytał dane
  if((file_r = open("magazyn.txt", O_RDONLY)) ==  -1)
        {
          perror("producent.open error");
          exit(1);
        }

    do
    {
    //Produkcja towaru, zapis do bufora niezaleznego

    semP(sm1);
    printf("SEM1|");semInfo(sm1);
    data=read(file_r,&producent,1);
    if(data==-1)
    {
      perror("read error");
      exit(1);
    }
  //  printf("\t\tProducent przeczytal: %s\n",producent);
    wpd->buf[wpd->tail]=producent;
    printf("\t\tProducent przeczytal: %s\n",wpd->buf);
    wpd->tail++;
    if(wpd->tail ==  NBUF)
    {
      wpd->tail=0;
    }
    semV(sm2);
    printf("SEM2|");semInfo(sm2);

}while(data>0);
  semV(sm2);
  wpd->buf[wpd->tail]=koniec;
  close(file_r);
  semClose(sm1);
  semClose(sm2);
  shmClose(wpd,fd,size_shm);
  exit(0);
}
