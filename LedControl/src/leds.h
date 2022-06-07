/**
* \file gpio.h
* \brief Built in Leds functions
*
* This module implements the functions to initialize and configurate the 4 built in board leds, LEDS are Active LOW
* \author Filipe Loureiro e Miguel Silva
* \date 07/06/22
* \version 5.1
* \bug No bugs detected
*/

#ifndef _LEDS_H    
#define _LEDS_H

#include "base.h"
#include "gpio.h"

#define PRINT_LOOP 0					    // For debug prints
#define LED1 13                                             // LED1 pin number of GPIO_0
#define LED2 14                                             // LED2 pin number of GPIO_0
#define LED3 15                                             // LED3 pin number of GPIO_0
#define LED4 16                                             // LED4 pin number of GPIO_0

///////////////////////////////////////////////////////////////////////////////////////
//  Public Functions:

/**
* \brief Built in Leds initialization function
*
* Initializes the board leds by using a byte for these porpouse, led 1 match to byte=1, led 2 match to byte=2, ect
*
* \param [IN] char n_leds           -> byte corresponding to the leds to connect {0,1,3,7,15}
* \param [IN] char c                -> 'H' or 'h' to initialize the leds to a logic 1
                                    -> 'L' or 'l' to initialize the leds to a logic 0
* \bug No bugs detected
*/
void leds_init(char n_leds, char c);

/*
* Set the board leds by using a byte for these porpouse, led 1 match to byte=1, led 2 match to byte=2, ect
*
* \param [IN] char n_leds           -> byte corresponding to the leds to connect {0,1,3,7,15}
* \param [IN] unsigned int state    -> 0 to set the leds to a logic 0, it means LED ON
                                    -> 1 to set the leds to a logic 1, it means LED OFF
* \bug No bugs detected
*/

void leds_set(int n_leds, int state);

///////////////////////////////////////////////////////////////////////////////////////
//  Private Functions:
  
#endif