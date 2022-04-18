#define _XOPEN_SOURCE 500
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "shmem.h"

int fd,nr_size;
struct stat info;
//Funkcja tworzy pamięć dzieloną o nazwie name i rozmiarze size.
//Funkcja zwraca deskryptor obiektu pamięci dzielonej.
int shmCreate(const char* name, int nr_size)
{
  fd=shm_open(name,O_RDWR | O_CREAT|O_EXCL,0664);
  if(fd==-1)
  {
    perror("shm error");
    exit(1);
  }
  if((ftruncate(fd,nr_size))==-1)
  {
    perror("ftruncate error");
    exit(1);
  }
  return fd;
}
//Funkcja otwiera obiekt pamięci dzielonej i zwraca jego deskryptor.
int shmOpen(const char* name)
{
  fd=shm_open(name, O_RDWR,0664);
  if(fd==-1)
  {
    perror("shm error");
    exit(1);
  }
  return fd;
}
//Usuwa obiekt pamięci dzielonej o nazwie name.
void shmRm(const char* name)
{
  if(shm_unlink(name)==-1)
  {
    perror("shm_unlink error");
    exit(1);
  }
  printf("Usuniety zostal segment pamieci dzielonej o nazwie: %s\n",name);
}
//Odwzorowuje obiekt pamięci dzielonej o deskryptorze fd i rozmiarze size w przestrzeń adresową procesu.
//Funkcja zwraca adres początku odwzorowanego obszaru pamięci dzielonej.
void* shmMap(int fd, int nr_size)
{
  char *ptr=mmap(NULL,nr_size, PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
   if ((void *)ptr == MAP_FAILED)
   {
     perror("Mmap error");
     exit(1);
   }
  return (void *)ptr;
}


//Usuwa odwzorowanie obiektu pamięci dzielonej i zamyka powiązany z nim deskryptor.
void shmClose(void *ptr, int fd, int nr_size)
{
  //Usuwa odwzorowanie obiektu pamięci dzielonej
  if(munmap(ptr,nr_size)==-1)
  {
    perror("munmap error");
    exit(1);
  }
  //Zamyka powiązany z nim deskryptor
  if(close(fd)==-1)
  {
    perror("close error");
    exit(1);
  }
}
//Zwraca rozmiar pamięci dzielonej określonej deskryptorem fd.
//Proszę użyć funkcji systemowej fstat.
int shmSize(int fd)
{

  if (fstat(fd, &info) != 0)
  {
    perror("fstat() error");
    exit(1);
  }
 else
 {
  printf("   size:   %ld\n",info.st_size);
  nr_size=info.st_size;
 }
 return nr_size;
}
//Wypisuje informacje o pamięci dzielonej:
// prawa dostępu, rozmiar, właściciel, etc.
void shmInfo(int fd)
{
  if (fstat(fd, &info) != 0)
     perror("fstat() error");
   else {
     printf("Wlasciwosci pamieci dzielonej:\n");
     printf("   size:   %ld\n",         info.st_size);
     printf("  inode:   %d\n",   (int) info.st_ino);
     printf(" dev id:   %d\n",   (int) info.st_dev);
     printf("   mode:   %o\n",       info.st_mode);
     printf("  links:   %ld\n",         info.st_nlink);
     printf("    uid:   %d\n",   (int) info.st_uid);
     printf("    gid:   %d\n",   (int) info.st_gid);
   }
}
