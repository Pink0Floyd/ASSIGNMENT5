/**
* \file pwm.h
* \brief Pulse Width Modulation module
*
* This module contains functions to implement PWM signals with variable duty-cycle
*
* \author Filipe Loureiro e Miguel Silva
* \date 13/06/22
* \version 5.2
* \bug No bugs detected
*/

#ifndef _PWM_H
#define _PWM_H 

#include "base.h"

#define PWM0_NID DT_NODELABEL(pwm0)

#define LED1 13                                             // LED1 pin number of GPIO_0
#define LED2 14                                             // LED2 pin number of GPIO_0
#define LED3 15                                             // LED3 pin number of GPIO_0
#define LED4 16                                             // LED4 pin number of GPIO_0

///////////////////////////////////////////////////////////////////////////////////////
//  Public Functions:

/**
* \brief PWM initialization function
*
* Initializes the PWM in order to use it 
*
* \bug No bugs detected
*/
void pwm_init();

/**
* \brief 
*
*\param [IN] uint16_t duty_cycle to set the PWM,[0 to 100]%
* \bug No bugs detected
*/
void pwm_led_set(uint16_t duty_cycle);

#endif