#==============================================================================
#															Makefile Zestaw 08
#==============================================================================
CC			:= gcc -std=c99 -pedantic
CFLAGS  := -O3 -Wall
LDFLAGS	:=	-s -pthread
LDLIBS	:= -L. -lmsg -lrt
.PHONE: all clean
all:serwer.x klient.x libmsg.so libmsg.a 

libmsg.a: msg.c msg.h
		    gcc -c msg.c
		    ar rv libmsg.a msg.o

libmsg.so: msg.c msg.h
	    gcc -c -O -fPIC msg.c
	    gcc -shared -o libmsg.so msg.o

serwer.x:	serwer.o libmsg.so libmsg.a
serwer.o:	serwer.c msg.h

klient.x:	klient.o libmsg.so libmsg.a
klient.o:	klient.c msg.h



%.x: %.o
		$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
		$(CC)	$(CFLAGS) -c	-o	$@	$<
clean:
	rm -f *.o *.x *.so *.a
