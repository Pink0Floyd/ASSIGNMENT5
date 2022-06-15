
/**
* \file str.h
* \brief A module with string manipulation functions
* 
* This module implements functions to manage and analise strings as an array of characters
* 
* \author Pink0Floyd
* \date 15/06/22
* \version 5.6
* \bug No bugs found
*/

#ifndef _STR_H
#define _STR_H

#include "base.h"

#define STR_MAX_LEN 32000	// must be less than 256*256/2-1 because its int16 max value

/**
*\brief String initialisation function
*
* Initialises each string position with the specified character
*
*\param [OUT] pointer to the first position of the initialised string
*\param [IN] length of the string to be initialised
*\param [IN] character specified to initialise the string
*\bug No bugs found
*/
void init_str(char* str,uint16_t length,char c);

/**
*\brief String length measure function
*
* Measures and returns the length of the string by finding the first '\0' character, return -1 if none is found
*
*\param [IN] pointer to the first position of the measuring string
*\return length of the string measured
*\bug No bugs found
*/
int16_t len_str(char* str);

/**
*\brief String character finding function
*
* Finds the first specified character and returns its position in a given length, returning -1 if it isn't found
*
*\param [IN] pointer to the first position of the given string
*\param [IN] character to be found in the string
*\param [IN] string length in which to find the specified character
*\return position of the first found matching character
*\bug No bugs found
*/
int16_t find_str_c(char* str,char c,uint16_t length);

/** 
*\brief String character range finding function
* 
* Finds the first of the specified range of characters and returns its position in a given length, return -1 if it isn't found
* 
* \param [IN] pointer to the first position of the given string
* \param [IN] first character in the range of characters to be found
* \param [IN] last character in the range of characters to be found
* \param [IN] string length in which to find the specified character
* \return position of the first found matching character
*/
int16_t find_str_cc(char* str,char ci,char cf,uint16_t length);

/**
*\brief String string finding function
*
* Finds the first specified string and returns its first position in a given length, returning -1 if it isn't found
*
*\param [IN] pointer to the first position of the given string
*\param [IN] pointer to the first position of the string to be found
*\param [IN] string length in which to find the specified characer
*\return position of the first found matching character
*\bug No bugs found
*/
int16_t find_str_str(char* str,char* str0,uint16_t length,uint16_t n);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
*\brief String copy function
*
* Copies a certain number of characters of a given string to the specified location
*
*\param [IN] pointer to the first position of the string to be copied
*\param [OUT] pointer to the first position of the string to which the string was copied
*\param [IN] length of the string to be copied
*\bug No bugs found
*/
void copy_str(char* str1,char* str2,uint16_t length);

#endif