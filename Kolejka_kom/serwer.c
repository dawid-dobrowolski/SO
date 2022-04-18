#include "msg.h"
#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
mqd_t mqdes_s,mqdes_k;
komunikat msg;
const char* nz_serwer="/serwer";
//przechwycenie sygnalu
void my_sighandler()
{
  printf("\nZamykam i usuwam kolejke serwera na zadanie sygnalu SYGINT\n");
  msgClose(mqdes_s);
  msgRm(nz_serwer);
  _exit(1);
}

//funkcja atexit
void koniec(void)
{
  msgClose(mqdes_s);
  msgRm(nz_serwer);
}

int main(int argc, char *argv[])
{

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
  mqdes_s=msgCreate(nz_serwer); //Utworzyć kolejkę komunikatów
  msgInfo(mqdes_s);
  int wynik;
  char nazwa_k[20];
  while(1)//Odbierać komunikaty od klientów ze swojej kolejki w pętli nieskończonej
  {
    //ustawiam kolejke na odbiór komunikatu
    msgRecv(mqdes_s,&msg);
    printf("Przeslano wiadomosc\n");
    printf("Sprawdzenie tokenow: PID:%d|toka:%d|tokb:%d|toko:%d\n",msg.pid,msg.a,msg.b,msg.o);
    sprintf(nazwa_k,"/%d",msg.pid);
   mqdes_k=msgOpen(nazwa_k);
    switch(msg.o)
    {
      case 43:
              wynik=msg.a+msg.b;
              printf("wynik operacji:%d\n",wynik);
              msg.wynik=wynik;
              msgSend(mqdes_k,&msg);
              break;

      case 45:
              wynik=msg.a-msg.b;
              printf("wynik operacji:%d\n",wynik);
              msg.wynik=wynik;
              msgSend(mqdes_k,&msg);
              break;

      case 42:
              wynik=msg.a*msg.b;
              printf("wynik operacji:%d\n",wynik);
              msg.wynik=wynik;
              msgSend(mqdes_k,&msg);
              break;

      case 47:
              wynik=msg.a/msg.b;
              printf("wynik operacji:%d\n",wynik);
              msg.wynik=wynik;
              msgSend(mqdes_k,&msg);
              break;
    }
    close(mqdes_k);
  }
  exit(0);
}
