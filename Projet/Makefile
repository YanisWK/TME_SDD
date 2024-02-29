#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -ggdb -Wno-unused-parameter 
CC = gcc

PROGRAMS =   ChaineMain

.PHONY:	all clean

all: $(PROGRAMS)


ChaineMain: Chaine.o ChaineMain.o SVGwriter.o
	$(CC) -o $@ $(CFLAGS) $^ -lm

Chaine.o: Chaine.c
	gcc $(CFLAGS) -c Chaine.c -lm

SVGwriter.o: SVGwriter.c
	$(CC) $(CFLAGS) -c compare.c

clean:
	rm -f *.o *~ $(PROGRAMS) 