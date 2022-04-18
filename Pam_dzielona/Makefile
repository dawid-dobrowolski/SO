#==============================================================================
#															Makefile Zestaw 07
#==============================================================================
CC			:= gcc -std=c99 -pedantic
CFLAGS  := -O3 -Wall
LDFLAGS	:=	-s -pthread
LDLIBS	:= -L. -lshmem -lrt -lsem
.PHONE: all clean
all:	shmuse.x glowny.x konsument.x producent.x libshmem.so libsem.a

libsem.a: sem.c sem.h
		    gcc -c sem.c
		    ar rv libsem.a sem.o

libshmem.so: shmem.c shmem.h
	    gcc -c -O -fPIC shmem.c
	    gcc -shared -o libshmem.so shmem.o


shmuse.x:	shmuse.o libshmem.so
shmuse.o: shmuse.c shmem.h

glowny.x:	glowny.o libshmem.so libsem.a
glowny.o:	glowny.c sem.h shmem.h

konsument.x:	konsument.o libshmem.so libsem.a
konsument.o:	konsument.c shmem.h sem.h

producent.x:	producent.o libshmem.so libsem.a
producent.o:	producent.c shmem.h sem.h

%.x: %.o
		$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
		$(CC)	$(CFLAGS) -c	-o	$@	$<
clean:
	rm -f *.o *.x *.so *.a
