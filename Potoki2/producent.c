#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#define S_MAX 8 // Size of static array
char buff[S_MAX];
int main(int argc,char* argv[])
{

    int file_r,data;
    int fifo;
    if(argc != 4)
      {
        printf("%s",argv[0]);
        exit(1);
      }
      if((file_r = open(argv[1], O_RDONLY)) ==  -1)
        {
          perror("open error");
          exit(1);
        }
      if((fifo = open(argv[3],O_WRONLY)) ==  -1)
        {
          perror("open error");
          exit(1);
        }
        while((data =read(file_r, buff, S_MAX)) > 0 )
        {
          if(write(fifo, buff, data) == -1)
          {
            perror("write error");
            exit(1);
          }
          sleep(rand()%4+1);
          printf("Producent przeczytal: %s o rozmiarze %d bajtow\n",buff,data);
        }
        if(data==-1)
        {
          perror("read error");
          exit(1);
        }
    if(close(fifo)==-1)
    {
      perror("close error");
      exit(1);
    }
    if(close(file_r)==-1)
    {
      perror("close error");
      exit(1);
    }
      exit(0);
    }
