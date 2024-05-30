CC = gcc
CFLAGS = -Wall -std=c99 -g
vcalc: vigesimal.o vcalc.o check.o

vigesimal.o: vigesimal.c vigesimal.h check.h
vcalc.o: vcalc.c vigesimal.h check.h
check.o: check.c check.h

vigesimal.c: vigesimal.h check.h
vcalc.c: vigesimal.h check.h
check.c: check.h

vigesimal.h: check.h

clean:
	rm -f vigesimal.o vcalc.o check.o