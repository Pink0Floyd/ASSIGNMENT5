/**
* \file uart.h
* \brief UART module
*
* This module implements the functions to initialise and interact with the UART
* 
* \author Filipe Loureiro & Miguel Silva
* \date 15/06/22
* \version 5.6
* \bug No bugs detected
*/

#ifndef _UART_H
#define _UART_H

#include <math.h>
#include <console/console.h>
#include "base.h"

///////////////////////////////////////////////////////////////////////////////////////
//  Public Functions:

/**
* \brief UART initialise function
*
* Initializes the UART to use it 
*
* \bug No bugs detected
*/
void uart_init();

/**
*\brief UART character reception function
*
* Receives a character from the UART
*
*\return byte of data received
*\bug No bugs found
*/
char get_char();

/**
*\brief UART character transmission function
*
* Sends a character through the UART
*
*\param [IN] byte of data to be transmitted
*\bug No bugs found
*/
void put_char(char c);

/**
*\brief EOL atomic function
*
* Sends cr and lf characters through the UART
*
*\bug No bugs found
*/
void put_eol();

/**
*\brief EOL function
*
* Sends some cr and lf characters through the UART
*
*\param [IN] number of lf to be inserted
*\bug No bugs found
*/
void put_neol(uint8_t n);

/**
*\brief TAB function
*
* Sends a TAB character through the UART
*
*\bug No bugs found
*/
void put_tab();

/**
*\brief TAB function
*
* Sends some TAB characters through the UART
*
*\param [IN] number of tabs to be inserted
*\bug No bugs found
*/
void put_ntab(uint8_t n);

/**
*\brief UART string transmission function
*
* Sends a string through the UART
*
*\param [IN] string to be transmitted 
*\bug No bugs found
*/
void put_str(char* str);

/**
*\brief UART string reception function
*
* Receives a string through the UART
*
*\param [OUT] string received
*\bug No bugs found
*/
void get_str(char* str,char term);

/**
*\brief UART unsigned integer atomic transmission function
*
* Sends 4 bits as a hexadecimal character
*
*\param [IN] value to be transmitted
*\bug No bugs found
*/
void put_uint4(uint8_t i);

/**
*\brief UART unsigned integer atomic reception function
*
* Receives 4 bits as a hexadecimal character
*
*\return value received
*\bug No bugs found
*/
uint8_t get_uint4();

#endif