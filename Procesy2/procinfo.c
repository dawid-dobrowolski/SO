//=================================================================================
// Author: Dawid Dobrowolski SO Group 7,
//=================================================================================
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "procinfo.h"

int procinfo(const char* name)
{
      uid_t UID   =   getuid();
      gid_t GID   =   getgid();
      pid_t PID   =   getpid();
      pid_t PPID  =   getppid();
      pid_t PGID  =   getpgrp();
  printf("Name = %s, UID: %d, GIT: %d, PID: %d, PPID: %d, PGID: %d  \n",name,UID,GID,PID,PPID,PGID);

  return 0;
}
