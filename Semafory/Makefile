#==============================================================================
#															Makefile Zestaw 06
#==============================================================================
CC			:= gcc -std=c99 -pedantic
CFLAGS  := -O3 -Wall -pthread
LDFLAGS	:= -pthread -s -lm
LDLIBS	:=	-L. -lrt -lsem
.PHONE: all clean

all: semuse.x prog.x powielacz.x test.x

semuse.x:	semuse.o libsem.a
semuse.o: semuse.c sem.h
libsem.a: sem.o
				ar rv libsem.a sem.o

prog.x:	prog.o libsem.a
prog.o:	prog.c sem.h
powielacz.x:	powielacz.o libsem.a
powielacz.o:	powielacz.c sem.h

test.x: test.o libsem.a
test.o: test.c sem.h

%.x: %.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^

%.o: %.c
	$(CC)	$(CFLAGS)	-c	-o	$@	$<
clean:
	$(RM) $(wildcard *.[ox])
