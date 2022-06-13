/**
* \file adc.h
* \brief UART module
*
* This module implements the functions to initialise and interact with the UART
* \brief  Use the console services instead of native UART functions
* \author Filipe Loureiro & Miguel Silva
* \date 13/06/22
* \version 3.1
* \bug No bugs detected
*/

#ifndef COM
#define COM

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
*\brief crlf atomic function
*
* Sends cr and lf characters through the UART
*
*\bug No bugs found
*/
void put_crlf();

/**
*\brief crlf function
*
* Sends some cr and lf characters through the UART
*
*\param [IN] number of lf to be inserted
*\bug No bugs found
*/
void put_ncrlf(uint8_t n);

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

/**
*\brief UART unsigned integer atomic transmission function
*
* Sends 8 bits as a hexadecimal characters
*
*\param [IN] value to be transmitted
*\param [IN] option to print "Ox" to indicate hexadecimal number
*\bug No bugs found
*/
void put_uint8(uint8_t i,uint8_t Ox);

/**
*\brief UART unsigned integer reception function
*
* Receives 8 bits as a hexadecimal character
*
*\return value received
*\bug No bugs found
*/
uint8_t get_uint8();

/**
*\brief UART unsigned integer transmission function
*
* Sends 16 bits as a hexadecimal characters
*
*\param [IN] value to be transmitted
*\param [IN] option to print "Ox" to indicate hexadecimal number
*\bug No bugs found
*/
void put_uint16(uint16_t i,uint8_t Ox);

/**
*\brief UART unsigned integer reception function
*
* Receives 16 bits as a hexadecimal character
*
*\return value received
*\bug No bugs found
*/
uint16_t get_uint16();

/**
*\brief UART unsigned integer transmission function
*
* Sends 32 bits as a hexadecimal characters
*
*\param [IN] value to be transmitted
*\param [IN] option to print "Ox" to indicate hexadecimal number
*\bug No bugs found
*/
void put_uint32(uint32_t i,uint8_t Ox);

/**
*\brief UART unsigned integer reception function
*
* Receives 32 bits as a hexadecimal character
*
*\return value received
*\bug No bugs found
*/
uint32_t get_uint32();

/**
*\brief UART unsigned integer transmission function
*
* Sends 64 bits as a hexadecimal characters
*
*\param [IN] value to be transmitted
*\param [IN] option to print "Ox" to indicate hexadecimal number
*\bug No bugs found
*/
void put_uint64(uint64_t i,uint8_t Ox);

/**
*\brief UART unsigned integer reception function
*
* Receives 64 bits as a hexadecimal character
*
*\return value received
*\bug No bugs found
*/
uint64_t get_uint64();

/**
*\brief UART integer transmission function
*
* Transmits an integer via UART
*
*\param [IN] integer to be transmitted
*\bug No bugs found
*/
void put_int(int i);

/**
*\brief UART integer reception function
*
* Receives an integer via UART
*
*\return integer received
*\bug No bugs found
*/
int get_int();

/**
*\brief UART float transmission function
*
* Transmits a float via UART
*
*\param [IN] float to be transmitted
*\bug No bugs found
*/
void put_float(float f);

/**
*\brief UART float transmission function
*
* Transmits a float via UART
*
*\param [IN] float to be transmitted
*\param [IN] number of integer algarisms
*\param [IN] number of floating algarisms
*\bug No bugs found
*/
void put_float_(float f,uint8_t ni,uint8_t nf);

#endif