#include <stdio.h>
#include <stdlib.h>
#include "sem.h"
sem_t *sem;
int main(int argc, char* argv[])
{
  if(argc!=2)
  {
    perror("Wrong number of arguments");
    exit(1);
  }
  const char* name="/semaforZ06";
  int value=1;
  switch(*argv[1])
  {
    case 'i':
              semCreate(name,value);
              break;
    case 'r':
              semOpen(name);
              semRemove(name);
              break;
    case 'p':
              semOpen(name);
              semP(sem);
              break;
    case 'v':
              semOpen(name);
              semV(sem);
              break;
    case 'q':
              semOpen(name);
              semInfo(sem);
              break;
  }
semClose(sem);
exit(0);
}
