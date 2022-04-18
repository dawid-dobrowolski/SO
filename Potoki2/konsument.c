#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#define RIGHTS 0666 // Rights Access - 0666 means that everbody has read and write access
#define S_MAX 4 // Size of static array
char buff[S_MAX];
int file_w,data;

int main(int argc,char* argv[])
{

    int file_w,data,fifo;
    if(argc != 4)
      {
        printf("%s",argv[0]);
        exit(1);
      }
      if((file_w  = open(argv[2],O_WRONLY | O_CREAT,RIGHTS)) ==  -1)
        {
          perror("open function error");
          exit(1);
        }
      if((fifo = open(argv[3], O_RDONLY)) ==  -1)
        {
          perror("Open function error");
          exit(1);
        }
      while((data =read(fifo, buff, S_MAX)) > 0 ){
      if(write(file_w, buff, data) == -1)
      {
        perror("write error");
        exit(1);
      }
      sleep(rand()%4+1);

      printf("Konsument zapisal: %s o rozmiarze %d bajtow\n",buff,data);

    }
    if(data==-1)
    {
      perror("read error");
      exit(1);
    }
    if(close(file_w)==-1)
    {
      perror("close error");
      exit(1);
    }
    exit(0);
    }
