#ifndef MSG_H
#define MSG_H
#include <fcntl.h>          
#include <sys/stat.h>
#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

//const char *nz_serwer = "/serwer_Z08";

typedef struct
{
    int pid;
    int a;
    int o;
    int b;
    int wynik;
} komunikat;

int msgCreate(const char *name);
int msgOpen(const char *name);
void msgClose(int mqdes);
void msgRm(const char *name);
void msgSend(int mqdes, komunikat *msg);
void msgRecv(int mqdes, komunikat *msg);
void msgInfo(int mqdes);

#endif
