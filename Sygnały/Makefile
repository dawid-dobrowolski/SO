#==============================================================================
#															Makefile Zestaw 03
#==============================================================================
CC			:= gcc -std=c99
CFLAGS  := -O3 -Wall
LDFLAGS	:= -s

.PHONE: all clean

all: obsluga.x wysylaj.x grupa.x 

procinfo.o:			procinfo.c procinfo.h

obsluga.x:			obsluga.o procinfo.o
obsluga.o:			obsluga.c procinfo.c

wysylaj.x:			wysylaj.o
wysylaj.o:			wysylaj.c

grupa.x:				grupa.o
grupa.o:				grupa.c


%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC)	$(CFLAGS)	-c	-o	$@	$<
clean:
	$(RM) $(wildcard *.[ox])
