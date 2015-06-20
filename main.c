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
#include "spi0.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <assert.h>

typedef union _t_ems22a_data{
	unsigned short all;
	struct {
		unsigned P1:1;
		unsigned S5:1;
		unsigned S4:1;
		unsigned S3:1;
		unsigned S2:1;
		unsigned S1:1;
		unsigned DATA:9;
	}bits;
} t_ems22a_data;

t_ems22a_data ems22a_data;

int main(int argc, char **argv) 
{
	int i;
	unsigned short ems22a_value;
	if (spi0_unidir_poll_init( 0x0400, SPI0_CPOL_HIGH |
			SPI0_CHPA_BEGINN) == -1) return -1;

	for (i = 0; i < 8; i++) {
		printf("read EMS22A\n");
		ems22a_data.all = spi0_poll_read_EMS22A();

		printf(
		"Value: %d;\n"
		"End of offset compensation algorithm(S1): %d;\n"
		"Cordic overfl ow indicating an error in cordic part: %d;\n"
		"Linearity alarm: %d;\n"
		"Increase in magnitude: %d;\n"
		"Decrease in magnitude: %d;\n"
		"Even parity: %d;\n",
		ems22a_data.bits.DATA,
		ems22a_data.bits.S1,
		ems22a_data.bits.S2,
		ems22a_data.bits.S3,
		ems22a_data.bits.S4,
		ems22a_data.bits.S5,
		ems22a_data.bits.P1		);
	}
	return 0;
}


/*
	int i;

//	if (init_piriph() == -1) {
//		printf("Failed\n");
//		return -1;
//	}

	// Сделаем GPIO26 выход, так поклацать.
	bcm2835_GPIO->GPFSEL2.bits.FSELn6 = GPIO_FSEL_OUTPUT;

	*
	 * a) Set CS, CPOL, CPHA as required and set TA = 1.
	 * b) Poll TXD writing bytes to SPI_FIFO, RXD reading bytes from
	 *    SPI_FIFO until all data written.
	 * c) Poll DONE until it goes to 1.
	 * d) Set TA = 0.
	 *
	printf("Write data to SPI\n");

	bcm2835_SPI->CSR.bits.CLEAR = 0x3;
	bcm2835_SPI->CLR = 400;

	*
	 * Бит REN нужно устанавливать толоько во время приёма данных.
	 * Нужно только придумать и понять как это делается.
	 * bcm2835_SPI->CSR.bits.REN = 0;
	 * UPD: Только для рыб... этот бит использовать только в bidirectional
	 * режиме.
	 *

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
*/
