# Makefile for spi
CC = gcc
objects = main.o bcm2835.o spi0.o

spi_test: $(objects)
	$(CC) -v -o spi_test $(objects)
	
main.o: main.c bcm2835.h
	$(CC) -c main.c

bcm2835.o: bcm2835.c bcm2835.h
	$(CC) -c bcm2835.c

spi0.o:
	$(CC) -c spi0.c
	
clean:
	rm *.o
