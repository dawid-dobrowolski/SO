#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#define RIGHTS 0666
#define SIZEP 10 
#define SIZE 5
char buff[SIZEP];
int file_w,file_r,data;


void producent(int fd)
{
  while((data =read(file_r, buff, SIZEP)) > 0 )
  {
    if(write(fd, buff, data) == -1)
    {
      perror("Transfer data error");
      exit(1);
    }

    sleep(rand()%4+1);
    printf("Producent przeczytal: %s o rozmiarze %d bajtow\n",buff,data);
  }
  if(data == -1)
  {
    perror("Read error");
    exit(1);
  }
}

void konsument(int fd)
{
  while((data =read(fd, buff, SIZE)) > 0 )
  {
  if(write(file_w, buff, data) == -1)
  {
    perror("Transfer data error");
    exit(1);
  }
  sleep(rand()%4+1);

printf("Konsument zapisal: %s o rozmiarze %d bajtow\n",buff,data);

}
if(data ==  -1)
{
  perror("Read error");
  exit(1);
}
}
int main(int argc,char* argv[])
{
    //  checking if the number of arguments is correct
    if(argc != 3)
      {
        printf("%s",argv[0]);
        exit(1);
      }

    //  creating pipe which return the descriptors to it into an array
    //  where
    //  fd[0] - for reading (in function read())
    //  fd[1] - for writing (in function write())
    int fd[2];
    if(pipe(fd) ==  -1)
    {
      perror("pipe error");
      exit(1);
    }

    //  open file, with data to write to pipe
    //  O_RDONLY  flag specifies read permission
    if((file_r = open(argv[1], O_RDONLY)) ==  -1)
      {
        perror("open function error");
        exit(1);
      }


    //  O_CREAT flag create a file if the pathname does not exist
    //  RIGHTS mode defines the rights access
    //  O_WRONLY flag specifies write permission
    if((file_w  = open(argv[2],O_WRONLY | O_CREAT,RIGHTS)) ==  -1)
      {
        perror("open function error");
        exit(1);
      }

    switch(fork())
    {
      case -1:
              perror("fork error");
              exit(1);
      case 0:
              //  parent process file descriptors are inherited by child process
              if(close(fd[1]) == -1)
              {
                perror("close error");
                exit(1);
              }

              konsument(fd[0]);

              if(close(fd[0]) ==  -1)
              {
                perror("close error");
                exit(1);
              }

              if(close(file_w)==-1)
              {
                perror("close error");
                exit(1);
              }

              break;
      default:
              if(close(fd[0]) == -1)
              {
                perror("close error");
                exit(1);
              }

              producent(fd[1]);

              if(close(fd[1]) ==  -1)
              {
                perror("close error");
                exit(1);
              }

              if(close(file_r)==-1)
                {
                  perror("close error");
                  exit(1);
                }

              if(wait(NULL)==-1)
                {
                  perror("fork error");
                  exit(1);
                }

                break;
    }

    exit(0);
}
