CC=gcc
CFLAGS=-Wall -pedantic -O3 -ffloat-store -fomit-frame-pointer -march=native
LFLAGS=-lm
EXEC=karney inv

all: $(EXEC)

karney: karney.c chisq.c
	$(CC) $(CFLAGS) karney.c chisq.c -o karney $(LFLAGS)

inv: inv.c chisq.c
	$(CC) $(CFLAGS) inv.c chisq.c -o inv $(LFLAGS)

clean:
	rm -f $(EXEC)
