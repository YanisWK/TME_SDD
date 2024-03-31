#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -ggdb -Wall -Wno-unused-parameter 
CC = gcc

PROGRAMS =   ChaineMain ReconstitueReseau

.PHONY:	all clean

all: $(PROGRAMS)



ChaineMain: Chaine.o ChaineMain.o SVGwriter.o reseau.o
	$(CC) -o $@ $(CFLAGS) $^ -lm

ReconstitueReseau: ReconstitueReseau.o Chaine.o SVGwriter.o reseau.o Hachage.o ArbreQuat.o
	$(CC) -o $@ $(CFLAGS) $^ -lm

ChaineMain.o: ChaineMain.c Chaine.h SVGwriter.h reseau.h
	gcc $(CFLAGS) -c ChaineMain.c  -lm

ReconstitueReseau.o: ReconstitueReseau.c Chaine.h SVGwriter.h reseau.h Hachage.h ArbreQuat.h
	$(CC) $(CFLAGS) -c ReconstitueReseau.c -lm

Chaine.o: Chaine.c Chaine.h
	gcc $(CFLAGS) -c Chaine.c -lm

SVGwriter.o: SVGwriter.c SVGwriter.h
	$(CC) $(CFLAGS) -c SVGwriter.c

reseau.o: reseau.c reseau.h
	$(CC) $(CFLAGS) -c reseau.c

Hachage.o: Hachage.c Hachage.h
	$(CC) $(CFLAGS) -c Hachage.c

ArbreQuat.o: ArbreQuat.c ArbreQuat.h
	$(CC) $(CFLAGS) -c ArbreQuat.c

clean:
	rm -f *.o *~ $(PROGRAMS) 