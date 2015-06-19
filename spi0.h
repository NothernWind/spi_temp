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
#ifndef SPI0_H
#define SPI0_H

void spi0_poll_init(int baud, int flags);
unsigned char spi0_poll_transfer(unsigned char data);

#endif // SPI_H
