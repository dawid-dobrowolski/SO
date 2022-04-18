#==============================================================================
#															Makefile Zestaw 10
#==============================================================================
CC			:= gcc -std=gnu99 -pedantic -Wall
CFLAGS  := -O3 -Wall -Wextra -pthread
LDFLAGS	:= -Wextra -pthread -lpthread
LDLIBS	:= -L. -lrt
.PHONE: all clean
all: piekarnia2.x piekarnia.x peterson1.x peterson2.x

piekarnia.x:	piekarnia.o
piekarnia.o:	piekarnia.c

piekarnia2.x:	piekarnia2.o
piekarnia2.o:	piekarnia2.c

peterson2.x:	peterson2.o
peterson2.o:	peterson2.c

peterson1.x:	peterson1.o
peterson1.o:	peterson1.c

%.x: %.o
		$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
		$(CC)	$(CFLAGS) -c	-o	$@	$<
clean:
	rm -f *.o *.x *.so *.a
