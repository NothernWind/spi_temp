/*!
 ********************************************************************
 * \file
 * \author	kaljan.nothern
 * \version	0.0.0
 * \date	01.03.2015
 * \brief
 *
 * Что сделать.
 * 1. переименовать файлы в spi0
 * 2. Прикрутить енкодер.
 *
 ********************************************************************
 */

#include "spi0.h"
#include "bcm2835.h"

void spi0_unidir_poll_init(int speed, int flags)
{
}

void spi0_unidir_dma_init(int speed, int flags)
{
}

unsigned char spi0_unidir_poll_transfer(unsigned char data)
{
	unsigned char temp;
	bcm2835_SPI->CSR.bits.TE_EN = 1;
	bcm2835_SPI->CSR.bits.TA = 1;
	bcm2835_SPI->FIFO = data;
	while (bcm2835_SPI->CSR.bits.DONE == 0);
	temp = (unsigned char)(bcm2835_SPI->FIFO);
	bcm2835_SPI->CSR.bits.TA = 0;
	return temp;
}

void spi_unidir_poll_buffer(const char * out, char * in, int size)
{
}
