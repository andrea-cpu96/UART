/*
 * uart.h
 *
 *  Created on: 17 nov 2022
 *      Author: andre
 */

#ifndef UART_H_
#define UART_H_


#define UART_2_BASE_ADDR			0x40004400U


typedef struct uart2Reg
{

	uint32_t uart_sr;
	uint32_t uart_dr;
	uint32_t uart_brr;
	uint32_t uart_cr1;
	uint32_t uart_cr2;
	uint32_t uart_cr3;
	uint32_t uart_gtpr;

}uart2Reg_t;


#define UART_2 					 (uart2Reg_t *)UART_2_BASE_ADDR;


void uart_Init(void);

void uart_MultiByte_Tx(uint8_t *dataBuff, uint8_t length);
void uart_SingleByte_Tx(uint8_t data);

void uart_MultiByte_Rx(uint8_t *dataBuff, uint8_t length);
void uart_SingleByte_Rx(uint8_t *data);


#endif /* UART_H_ */
