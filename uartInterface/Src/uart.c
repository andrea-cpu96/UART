/*
 * uart.c
 *
 *  Created on: 17 nov 2022
 *      Author: andre
 */


#include <stdint.h>

#include "uart.h"

uart2Reg_t *huart2 = UART_2;


void uart_Init(void)
{

	// 16 MHz

	// Enable clock for UART2

	uint32_t *pRccBaseAddr = (uint32_t *)0x40023800U;

	uint32_t *pRccAPB1 = (uint32_t *)( (uint32_t)pRccBaseAddr + 0x40U );

	*pRccAPB1 |= ( 1 << 17 );

	/* Baud rate configuration BRR */

	// BR = 9600 = fck / ( 16 * USARTDIV )
	// USARTDIV = fck / ( 16 * 9600 ) = 104.16
	// DIV_FRACTION = 16 * 0.16 = 3 = 0x3
	// DIV_MANTISSA = 104 = 0x68
	// USART_BRR = 0x683

	huart2->uart_brr = 0x683U; // 9600 baud rate


	/* Control register configuration CR1 */

	// word length

	huart2->uart_cr1 &= ~( 1 << 12 ); // 8 bits of data

	// uart enable

	huart2->uart_cr1 |= ( 1 << 13 ); // uart enabled

	// receiver enable

	huart2->uart_cr1 |= ( 1 << 2 ); // RE

	// transmission enable

	huart2->uart_cr1 |= ( 1 << 3 ); // TE


	/* Control register configuration CR2 */

	// stop bits

	huart2->uart_cr2 &= ~( 0x3 << 12 );


}


void uart_MultiByte_Tx(uint8_t *dataBuff, uint8_t length)
{

	for(int i = 0 ; i < length ; i++)
		uart_SingleByte_Tx(dataBuff[i]);

}

void uart_SingleByte_Tx(uint8_t data)
{

	// Write the data into the data register

	huart2->uart_dr  = data;

	// Wait until the transmission completes

	while( ! ( huart2->uart_sr & ( 1 << 6  ) ) ); // TC == 1

}


void uart_MultiByte_Rx(uint8_t *dataBuff, uint8_t length)
{

	for(int i = 0 ; i < length ; i++)
		uart_SingleByte_Rx(&dataBuff[i]);

}

void uart_SingleByte_Rx(uint8_t *data)
{

	// Wait until the data register is not empty

	while( ! ( huart2->uart_sr & ( 1 << 5  ) ) ); // RXNE == 1

	// Read data from data register

	*data = huart2->uart_dr;


}

