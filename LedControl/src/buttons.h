/**
* \file buttons.h
* \brief Buttons functions
*
* This module implements the functions to initialize and use the built in board buttons
* \author Filipe Loureiro e Miguel Silva
* \date 18/06/22
* \version 5.3
* \bug No bugs detected
*/

#ifndef _BUTTONS_H
#define _BUTTONS_H

#include "base.h"
#include "gpio.h"
	    
#define PRINT_BUTTONS_DEBUG 1						// For debug prints				  

#define BUTTON1 11                                          // BUTTON1 pin number of GPIO_0
#define BUTTON2 12                                          // BUTTON2 pin number of GPIO_0
#define BUTTON3 24                                          // BUTTON3 pin number of GPIO_0
#define BUTTON4 25                                          // BUTTON4 pin number of GPIO_0

///////////////////////////////////////////////////////////////////////////////////////
// Private Functions:

//void reset_flag(uint8_t n);
//void buttons_callback_init(char n_buttons);

///////////////////////////////////////////////////////////////////////////////////////
// Public Functions:

/**
* \brief Built in Buttons initialization function without interrupts
*
* Initializes the board buttons by using a byte for these porpouse, button 1 match to byte=1, button 2 match to byte=2, ect
*
* \param [IN] char n_buttons        -> byte corresponding to the buttons to activate
* \bug No bugs detected
*/

void buttons_init(char n_buttons);


/**
* \brief Built in Buttons initialization function with interrupts
*
* Initializes the board buttons by using a byte for these porpouse, button 1 match to byte=1, button 2 match to byte=2, ect
*
* \param [IN] char n_buttons        -> byte corresponding to the buttons to activate
* \param [IN] char c                -> 'H' or 'h' to interrupt at rising edge
                                    -> 'L' or 'l' to interrupt at falling edge
                                    -> 'B' or 'b' to interrupt at both edges
* \bug No bugs detected
*/

void buttons_init_(char n_buttons, char c);

/**
* \brief Read Buttons Flags
*
* Return the current flag button state
*
* \param [IN] int button	    -> the button number for read the flag 
* \bug No bugs detected
*/
uint8_t read_buttons(uint8_t button);

#endif