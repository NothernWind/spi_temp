/*!
 ********************************************************************
 * \file
 * \author	kaljan.nothern
 * \version	0.0.0
 * \date
 * \brief
 *
 ********************************************************************
 */
#include "bcm2835.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <assert.h>

int main(int argc, char **argv) 
{
	int i;

	if (init_piriph() == -1) {
		printf("Failed\n");
		return -1;
	}

	// Сделаем GPIO26 выход, так поклацать.
	bcm2835_GPIO->GPFSEL2.bits.FSELn6 = GPIO_FSEL_OUTPUT;
	
	/*
	 * a) Set CS, CPOL, CPHA as required and set TA = 1.
	 * b) Poll TXD writing bytes to SPI_FIFO, RXD reading bytes from 
	 *    SPI_FIFO until all data written.
	 * c) Poll DONE until it goes to 1.
	 * d) Set TA = 0.
	 */
	printf("Write data to SPI\n");
	
	bcm2835_SPI->CSR.bits.CLEAR = 0x3;
	bcm2835_SPI->CLR = 400;

	/*
	 * Бит REN нужно устанавливать толоько во время приёма данных.
	 * Нужно только придумать и понять как это делается.
	 * bcm2835_SPI->CSR.bits.REN = 0;
	 * UPD: Только для рыб... этот бит использовать только в bidirectional
	 * режиме.
	 */

	bcm2835_SPI->CSR.bits.TE_EN = 1;
	bcm2835_SPI->CSR.bits.TA = 1;
	
	bcm2835_GPIO->GPSET0.bits.GPIO26 = 1;

	i = 1000;
	while(i--); 

	for (i = 0; i < 8; i++) {
		bcm2835_SPI->FIFO = 0xAA;
	}

	while (bcm2835_SPI->CSR.bits.DONE == 0);
	bcm2835_SPI->CSR.bits.TA = 0;
	bcm2835_GPIO->GPCLR0.bits.GPIO26 = 1;

	printf("Complete\n");

	printf("\nDeinit\n");
	bcm2835_SPI->CSR.bits.TE_EN = 0;
	periph_unmap(&gpio_dsc);
	periph_unmap(&spi_dsc);
	
	// DeInit
	return 0;
}
