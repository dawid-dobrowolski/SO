#==============================================================================
#															Makefile Zestaw 02
#==============================================================================
CC			:= gcc -std=c99
CFLAGS  := -O3 -Wall
LDFLAGS	:= -s

.PHONE: all clean

all: drzewko1.x drzewko2.x macierzysty.x potomny.x zombi.x orphan.x execute.x

drzewko1.x:			drzewko1.o	procinfo.o
drzewko1.o:			drzewko1.c	procinfo.c

drzewko2.x:			drzewko2.o	procinfo.o
drzewko2.o:			drzewko2.c	procinfo.c

macierzysty.x:	macierzysty.o	procinfo.o
macierzysty.o:	macierzysty.c procinfo.c

procinfo.o:			procinfo.c procinfo.h

potomny.x:			potomny.o	procinfo.o
potomny.o:			potomny.c procinfo.h

zombi.x:				zombi.o
zombi.o:				zombi.c

orphan.x:				orphan.o
orphan.o:				orphan.c

execute.x:			execute.o
execute.o:			execute.c


%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC)	$(CFLAGS)	-c	-o	$@	$<
clean:
	$(RM) $(wildcard *.[ox])
