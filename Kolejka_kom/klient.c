#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "msg.h"
const char* nazwa_k_global;
const char* nz_serwer="/serwer";
komunikat msg;
void my_sighandler()
{
  printf("\nZamykam kolejke serwera i usuwam kolejke klienta na zadanie sygnalu SYGINT\n");
  //msgClose(mqdes_s);
  msgRm(nazwa_k_global);
  _exit(1);
}

//funkcja atexit,zamknac kolejke serwera i usuwa wlasna kolejke
void koniec(void)
{
  //msgClose(mqdes_s);
  msgRm(nazwa_k_global);
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
   // zmienne potrzebne do wyizolowania tokenow
  char korektor_operatory[]={"+,-,*,/"};
  char korektor_liczby[]={"0,1,2,3,4,5,6,7,8,9"};
  char *schowek;
  char *schowek2;
  char dzialanie[20];
  char dzialanie2[20];
  char nazwa_k[20];

  //ustawiam nazwe kolejki na /PID
  int pid=getpid();
  printf("PID:%d\n",pid);
  sprintf(nazwa_k,"/%d",pid);
  printf("Nazwa:%s\n",nazwa_k);
  nazwa_k_global=nazwa_k;

  mqd_t mqdes_k=msgCreate(nazwa_k); //Utworzyc kolejke komunikatow w trybue do odbierania o nazwie /PID
  msgInfo(mqdes_k);
  mqd_t mqdes_s=msgOpen(nz_serwer);
  msgInfo(mqdes_s);

  while(1)
  {
    // przerwanie petli przez CTRL D
    printf("Prosze podac odpowiednie dzialanie:");
     if(fgets(dzialanie,10,stdin)==NULL)
    {
      break;
    }

    strcpy(dzialanie2,dzialanie);
    
    schowek=strtok(dzialanie,korektor_operatory);
    int tok_a=atoi(schowek);
    schowek=strtok(NULL,korektor_operatory);
    int tok_b=atoi(schowek);
    schowek2=strtok(dzialanie2,korektor_liczby);
    msg.pid=pid;
    msg.a=tok_a;
    msg.b=tok_b;
    msg.o=(int)*schowek2;
    if(msg.o==47 && msg.b==0)
    {
      printf("niedozwolone dzielenie przez 0\n");
      exit(1);
    }
    msgSend(mqdes_s,&msg);

    //zawiera komunikat ze zwroconym wynikiem
    msgRecv(mqdes_k,&msg);
    printf("Odpowiedz zwrotna|wynik operacji:%d\n",msg.wynik);
  }
  exit(0);
}
