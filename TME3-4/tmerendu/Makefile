#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -g -Wno-unused-parameter 
CC = gcc

PROGRAMS =   Biblio compare tests_LC tests_H

.PHONY:	all clean

all: $(PROGRAMS)


Biblio: entreeSortieLC.o BiblioLC.o main.o entreeSortieH.o BiblioH.o 
	$(CC) -o $@ $(CFLAGS) $^ -lm

compare: entreeSortieLC.o BiblioLC.o compare.o entreeSortieH.o BiblioH.o
	$(CC) -o $@ $(CFLAGS) $^ -lm

tests_LC: entreeSortieLC.o BiblioLC.o tests_LC.o
	$(CC) -o $@ $(CFLAGS) $^ -lm

tests_H: entreeSortieLC.o BiblioLC.o entreeSortieH.o BiblioH.o tests_H.o
	$(CC) -o $@ $(CFLAGS) $^ -lm

entreeSortieLC.o: entreeSortieLC.c
	gcc $(CFLAGS) -c entreeSortieLC.c

BiblioLC.o: BiblioLC.c
	gcc $(CFLAGS) -c BiblioLC.c

BiblioH.o: BiblioH.c
	gcc $(CFLAGS) -c BiblioH.c -lm

entreeSortieH.o: entreeSortieH.c
	gcc $(CFLAGS) -c entreeSortieH.c

main.o: main.c biblioLC.h 
	$(CC) $(CFLAGS) -c $<

compare.o: compare.c
	$(CC) $(CFLAGS) -c compare.c

tests_LC.o: tests_LC.c biblioLC.h
	$(CC) $(CFLAGS) -c tests_LC.c

tests_H.o: tests_H.c biblioH.h
	$(CC) $(CFLAGS) -c tests_H.c

clean:
	rm -f *.o *~ $(PROGRAMS) 