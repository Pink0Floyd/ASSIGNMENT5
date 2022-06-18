/**
* \file uart.h
* \brief UART module
*
* This module implements the functions to initialise and interact with the UART
* 
* \author Filipe Loureiro & Miguel Silva
* \date 18/06/22
* \version 5.8
* \bug No bugs detected
*/

#ifndef _UART_H
#define _UART_H

#include <math.h>
#include <console/console.h>
#include "base.h"

#define ECO_EN 1

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
*\brief UART integer reception function
*
* Receives an integer via UART
*
*\return integer received
*\bug No bugs found
*/
int get_int();

#endif