#==============================================================================
#															Makefile Zestaw 05
#==============================================================================
CC			:= gcc -std=c99 -pedantic 
CFLAGS  := -O3 -Wall
LDFLAGS	:= -s

.PHONE: all clean

all: fifo.x producent.x konsument.x

fifo.x:	fifo.o
fifo.o:	fifo.c

producent.x:	producent.o
producent.o: 	producent.c

konsument.x:	konsument.o
konsument.o:	konsument.c

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC)	$(CFLAGS)	-c	-o	$@	$<
clean:
	$(RM) $(wildcard *.[ox])
