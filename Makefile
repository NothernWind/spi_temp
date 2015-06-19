# Makefile for gpio
CC = gcc
objects = main.o bcm2835.o spi.o

gpio_test: $(objects)
	$(CC) -v -o spi_test $(objects)
	
main.o: main.c bcm2835.h
	$(CC) -c main.c

bcm2835.o: bcm2835.c bcm2835.h
	$(CC) -c bcm2835.c

spi.o:
	$(CC) -c spi.c
	
clean:
	rm *.o
