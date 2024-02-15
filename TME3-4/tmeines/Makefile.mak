CC = gcc
CFLAGS = -Wall -Wextra 
TARGET = main

all: $(TARGET)

$(TARGET): main.o biblioLC.o entreeSortieLC.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o biblioLC.o entreeSortieLC.o

main.o: main.c entreeSortieLC.h biblioLC.h
	$(CC) $(CFLAGS) -c main.c

biblioLC.o: biblioLC.c biblioLC.h
	$(CC) $(CFLAGS) -c biblioLC.c

entreeSortieLC.o: entreeSortieLC.c entreeSortieLC.h biblioLC.h
	$(CC) $(CFLAGS) -c entreeSortieLC.c

clean:
	rm -f *.o $(TARGET)