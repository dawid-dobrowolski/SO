#include "msg.h"
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


int msgCreate(const char *name)
  {
    mqd_t mqdes = mq_open(name, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, NULL);
    if (mqdes == (mqd_t)-1)
    {
        perror("mq_open error");
        exit(1);
    }
    printf("Utworzono kolejke komunikatow o nazwie: %s\n", name);
    return mqdes;
  }

int msgOpen(const char *name) {
    mqd_t mqdes = mq_open(name, O_RDWR);
    if (mqdes == -1) {
        perror("mq_open error");
        exit(1);
    }
    printf("Uzyskano dostep do kolejki komunikatow: %s, deskryptor: %d\n", name, mqdes);
    return mqdes;
}

void msgClose(int mqdes) {
    if(mq_close(mqdes) == -1) {
        perror("mq_close error");
        exit(1);
    }
    printf("Zamknieto kolejke komunikatow o deskryptorze: %d\n", mqdes);
}

void msgRm(const char *name) {
    if(mq_unlink(name) == -1){
        perror("mq_unlink error");
        exit(1);
    }
    printf("Usunieto kolejke komunikatow o nazwie: %s\n", name);
}

void msgSend(int mqdes, komunikat *msg) {
    if(mq_send(mqdes, (const char*)msg, sizeof(komunikat) + 1, 1) == -1) {
        perror("mq_send error");
        exit(1);
    }
}

void msgRecv(int mqdes, komunikat *msg) {
    if(mq_receive(mqdes, (char *)msg, 10000, NULL) == -1) {
        perror("mq_receive error");
        exit(1);
    }
    printf("Odebrano komunikat|PID:%d|tokeny: a=%d, o=%c, b=%d\n",msg->pid,msg->a,msg->o,msg->b);
}

void msgInfo(int mqdes) {
    struct mq_attr attr;
    if(mq_getattr(mqdes, &attr) == -1) {
        perror("mq_getattr error");
        exit(1);
    }
    printf("mq_flags        :%lX\n", attr.mq_flags);
    printf("mq_maxmsg       :%ld\n", attr.mq_maxmsg);
    printf("mq_msgsize      :%ld\n", attr.mq_msgsize);
    printf("mq_curmsgs      :%ld\n", attr.mq_curmsgs);
}
