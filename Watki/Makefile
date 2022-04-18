#==============================================================================
#															Makefile Zestaw 09
#==============================================================================
CC			:= gcc -std=gnu99 -pedantic -Wall
CFLAGS  := -O2 -Wall -Wextra -pthread
LDFLAGS	:= -Wextra -pthread -lpthread
LDLIBS	:= -L. -lrt
.PHONE: all clean
all:wykluczanie.x 

wykluczanie.x:	wykluczanie.o
wykluczanie.o:	wykluczanie.c

%.x: %.o
		$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
		$(CC)	$(CFLAGS) -c	-o	$@	$<
clean:
	rm -f *.o *.x *.so *.a
