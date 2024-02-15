#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -g -Wno-unused-parameter
CC = gcc

PROGRAMS =   Biblio 

.PHONY:	all clean

all: $(PROGRAMS)



Biblio: entreeSortieLC.o BiblioLC.o main.o
	$(CC) -o $@ $(CFLAGS) $^

entreeSortieLC.o: entreeSortieLC.c
	gcc $(CFLAGS) -c entreeSortieLC.c

BiblioLC.o: BiblioLC.c
	gcc $(CFLAGS) -c BiblioLC.c

main.o: main.c 
	gcc $(CFLAGS) -c main.c

#Ou plus simplement
#%.o:%.c %.h
#	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(PROGRAMS)