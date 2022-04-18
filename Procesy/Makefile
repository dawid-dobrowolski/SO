#==============================================================================
#															Makefile Zestaw 01
#==============================================================================
CC			:= gcc -std=c99
CFLAGS  := -O3 -Wall
LDFLAGS	:= -s

.PHONE: all clean

all: main.x kopiuj.x lider.x procesy.x

main.x:	main.o procinfo.o
main.o: main.c procinfo.h
procinfo.o:	procinfo.c procinfo.h

kopiuj.x: kopiuj.o
kopiuj.o: kopiuj.c

lider.x: lider.o procinfo.o
lider.o: lider.c procinfo.c

procesy.x: procesy.o procinfo.o
procesy.o: procesy.c procinfo.c



%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC)	$(CFLAGS)	-c	-o	$@	$<
clean:
	$(RM) $(wildcard *.[ox])
