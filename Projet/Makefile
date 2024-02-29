#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -ggdb -Wno-unused-parameter 
CC = gcc

PROGRAMS =   ChaineMain

.PHONY:	all clean

all: $(PROGRAMS)


ChaineMain: Chaine.o ChaineMain.o SVGwriter.o
	$(CC) -o $@ $(CFLAGS) $^ -lm

ChaineMain.o: ChaineMain.c Chaine.h SVGwriter.h
	gcc $(CFLAGS) -c ChaineMain.c 

Chaine.o: Chaine.c Chaine.h
	gcc $(CFLAGS) -c Chaine.c -lm

SVGwriter.o: SVGwriter.c SVGwriter.h
	$(CC) $(CFLAGS) -c SVGwriter.c

clean:
	rm -f *.o *~ $(PROGRAMS) 