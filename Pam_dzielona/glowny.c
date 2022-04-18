// Pseudokod dla problemu Producenta i Konsumenta z buforem cyklicznym.
// Wspolny bufor do przesylania danych znajduje sie w pamieci dzielonej.
// Dostep do bufora jest synchronizowany semaforami.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "shmem.h"
#include "sem.h"

#define NELE 20
#define NBUF 5

sem_t *sm1;
sem_t *sm2;
int value_sem1=NBUF;
int value_sem2=0;
const char* sem1="/semafor_1";
const char* sem2="/semafor_2";

int fd;
char* ptr;
const char* memoryname="/shared_memory";
const int size_shm=1024;



//wlasna oblsuga sygnalu
void my_sighandler()
{
  printf("\nUsuwam semafory i segment pamieci dzielonej na zadanie sygnalu SYGINT\n");
  semRemove(sem1);
  semRemove(sem2);
  shmRm(memoryname);
  _exit(1);
}

//funkcja atexit
void koniec(void)
{
  semRemove(sem1);
  semRemove(sem2);
  shmRm(memoryname);
}


int main(int argc, char* argv[])
{
  //Atexit
  if(atexit(koniec)!=0)
  {
    perror("atexit error:");
    _exit(1);
  }

  //ustawienie obslugi sygnalu
  if(signal(SIGINT,my_sighandler)==SIG_ERR)
   {
     perror("signal error");
     exit(1);
   }

//Utworzenie semaforów
sm1=semCreate(sem1,value_sem1);
semInfo(sm1);
sleep(2);
sm2=semCreate(sem2,value_sem2);
semInfo(sm2);
//Utworzenie segmentu pamieci dzielonej
fd=shmCreate(memoryname,size_shm);
sleep(1);
shmInfo(fd);
//Stworzenie potomków
 switch(fork())
  {
    case -1:
            perror("fork error");
            _exit(1);
    case 0:

            if((execl("./producent.x","producent.x",argv[1],argv[2],NULL))==-1)
            {
              perror("exec error");
              _exit(1);
            }
            break;
  }

 switch(fork())
  {
    case -1:
            perror("fork error");
            _exit(1);
    case 0:

            if((execl("./konsument.x","konsument.x",argv[1],argv[2],NULL))==-1)
            {
              perror("exec error");
              _exit(1);
            }
            break;
  }
wait(NULL);
wait(NULL);
exit(0);
}
