CFLAGS = -g -Wno-unused-parameter
CC = gcc

PROGRAMS = test


all: $(PROGRAMS)

test: entreeSortieLC.o BiblioLC.o main.o
	$(CC) -o $@ $(CFLAGS) $^

entreeSortieLC.o: entreeSortieLC.c
	gcc $(CFLAGS) -c entreeSortieLC.c

BiblioLC.o: BiblioLC.c
	gcc $(CFLAGS) -c BiblioLC.c

main.o: main.c 
	gcc $(CFLAGS) -c main.c

clean:
	rm -f *.o *~ $(PROGRAMS)
