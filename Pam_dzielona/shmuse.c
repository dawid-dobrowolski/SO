#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shmem.h"

char *ptr;
int fd;
struct stat info;
int nr_size;
const char* name="/sharedmemory";
int main(int argc, char* argv[])
{

  if(argc>3)
  {
    perror("wrong number of arguments");
    exit(1);
  }
if(argc>1)
{
int wybor=(int)*argv[1];
 switch(wybor)
  {
    case 99:
              //  Tworzy segment pamięci dzielonej o rozmiarze size bajtów
               nr_size  = atoi(argv[2]);
               shmCreate(name,nr_size);
               printf("Utworzono obszar pamieci dzielonej o nazwie: %s\n",name);
               close(fd);
               break;
    case 100:
              //  Usuwa segment pamięci dzielonej
              shmRm(name);
              break;
    case 114:
              //  Wypisuje zawartość pamięci dzielonej na standardowe wyjście
              shmOpen(name);
              shmSize(fd);
              ptr=shmMap(fd,nr_size);
              printf("Tekst z pamięci dzielonej: %s\n",ptr);
              shmClose(ptr,fd,nr_size);
              break;
    case 119:
              //  Kopiuje zawartośc standardowego wejścia do pamięci dzielonej. Sprawdzić rozmiar segmentu
                shmOpen(name);
                shmSize(fd);
                printf("Otworzono obszar pamieci dzielonej o nazwie: %s\n",name);
                ptr=shmMap(fd,nr_size);

                int data =read(STDIN_FILENO, ptr, nr_size);
                if(data == -1)
                {
                  perror("Read error");
                  exit(1);
                }
                printf("\nPrzeniesiono:%s do pamieci\n",ptr);
                shmClose(ptr,fd,nr_size);
                break;
    case 105:
              shmOpen(name);
              shmInfo(fd);
              close(fd);
              break;
}
}
if(argc==1)
{
//Wypisuje inforamcje o użyciu tego programu
printf("\n****************************************TEST.C****************************************\n");
printf("Program przyjmuje jednoliterowy argument i ewentualnie drugi argument:\n\n");
printf("\t./shmuse.x c size - Tworzy segment pamięci dzielonej o rozmiarze size bajtów\n");
printf("\t./shmuse.x d - Usuwa segment pamięci dzielonej\n");
printf("\t./shmuse.x r - Wypisuje zawartość pamięci dzielonej na standardowe wyjście\n");
printf("\t./shmuse.x w < input.txt - Kopiuje zawartość standardowego wejścia do pamięci dzielonej\n");
printf("\t./shmuse.x i - Wypisuje informacje o pamięci dzielonej\n");
printf("\t./shmuse.x - Wypisuje informacje o użyciu tego programu\n\n");
}
exit(0);
}
