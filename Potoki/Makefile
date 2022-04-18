#==============================================================================
#															Makefile Zestaw 04
#==============================================================================
CC			:= gcc -std=c99 -pedantic
CFLAGS  := -O3 -Wall
LDFLAGS	:= -s

.PHONE: all clean

all: prodkons.x
	
prodkons.x:	prodkons.o
prodkons.o:	prodkons.c

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC)	$(CFLAGS)	-c	-o	$@	$<
clean:
	$(RM) $(wildcard *.[ox])
