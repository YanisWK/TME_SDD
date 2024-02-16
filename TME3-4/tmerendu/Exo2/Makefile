#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -g -Wno-unused-parameter
CC = gcc

PROGRAMS =   Biblio 

.PHONY:	all clean

all: $(PROGRAMS)



Biblio: entreeSortieLC.o BiblioLC.o main.o biblioH.o
	$(CC) -o $@ $(CFLAGS) $^



entreeSortieLC.o: entreeSortieLC.c
	gcc $(CFLAGS) -c entreeSortieLC.c

BiblioLC.o: BiblioLC.c
	gcc $(CFLAGS) -c BiblioLC.c


main.o: main.c biblioLC.h biblioH.h
	$(CC) $(CFLAGS) -c $<



biblioH.o: biblioH.c biblioH.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *~ $(PROGRAMS) 