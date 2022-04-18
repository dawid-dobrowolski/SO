#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shmem.h"
#include "sem.h"
#define NELE 5
#define NBUF 5
#define RIGHTS 644


const char* memoryname="/shared_memory";
const char* sem1="/semafor_1";
const char* sem2="/semafor_2";
const int size_shm=1024;

int fd;
int file_w,data;
sem_t *sm1;
sem_t *sm2;
char pomocniczy;
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

  if((file_w  = open("schowek.txt",O_WRONLY | O_CREAT|O_TRUNC,RIGHTS)) ==  -1)
          {
            perror("open function error");
            exit(1);
          }
          sm1=semOpen(sem1);
          printf("SEM1|");semInfo(sm1);
          sm2=semOpen(sem2);
          printf("SEM2|");semInfo(sm2);
          fd=shmOpen(memoryname);
          shmInfo(fd);
            sleep(1);
          //odwzorowuje
          Towar *wpd=(Towar *)mmap(NULL,sizeof(Towar),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

  while(1)
  {
      semP(sm2);
      printf("SEM2|");semInfo(sm2);
      pomocniczy=(wpd->buf[wpd->head]);
     if(wpd->buf[wpd->tail]==koniec)
      {
        break;
      }
      printf("\t\t\tKonsument zapisal: %s\n",wpd->buf);
      if(write(file_w,&pomocniczy,1) == -1)
      {
        perror("Transfer data error");
        exit(1);
      }
      else{
      wpd->head=(wpd->head+1) % NBUF;

      semV(sm1);
      printf("SEM1|");semInfo(sm1);
      }

  }
    sleep(1);
    close(file_w);
    semClose(sm1);
    semClose(sm2);
    shmClose(wpd,fd,size_shm);
    exit(0);
  }
