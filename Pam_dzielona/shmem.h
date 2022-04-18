#ifndef SHM_H
#define SHM_H
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int shmCreate(const char* name, int size);
int shmOpen(const char* name);
void shmRm(const char* name);
void* shmMap(int fd, int size);
void shmClose(void *ptr, int fd, int size);
int shmSize(int fd);
void shmInfo(int fd);

#endif
