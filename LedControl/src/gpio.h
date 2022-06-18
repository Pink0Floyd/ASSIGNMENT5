/**
* \file gpio.h
* \brief GPIO functions
*
* This module implements the functions to initialize and do some gpio configuration
* \author Filipe Loureiro e Miguel Silva
* \date 18/06/22
* \version 5.4
* \bug No bugs detected
*/

#ifndef _GPIO_H
#define _GPIO_H

#include "base.h"

#define PRINT_GPIB_DEBUG 0							// For debug prints

#define GPIO0_NID DT_NODELABEL(gpio0)                       // Get the gpio0 identifier from the device tree
#define GPIO1_NID DT_NODELABEL(gpio1)                       // Get the gpio0 identifier from the device tree

#define GPIO0_LABEL DT_LABEL(GPIO0_NID)                     // Get the gpio0 label from the device tree
#define GPIO1_LABEL DT_LABEL(GPIO1_NID)                     // Get the gpio0 label from the device tree

///////////////////////////////////////////////////////////////////////////////////////
//  Public Functions:

/**
* \brief GPIO 0 initialization function
*
* Initializes the GPIO 0 to use the pins
*
* \return Return a pointer to a device struct type
* \bug No bugs detected
*/

struct device *gpio0_init();

/**
* \brief GPIO 1 initialization function
*
* Initializes the GPIO 1 to use the pins
*
* \return Return a pointer to a struct of device type
* \bug No bugs detected
*/
struct device *gpio1_init();

///////////////////////////////////////////////////////////////////////////////////////
//  Private Functions:

/**
* \brief GPIO 0 binding function
*
*Bind the struct to the device GPIO 0
*
* \return Return a pointer to a device struct type
* \bug No bugs detected
*/
void gpio0_bind();

/**
* \brief GPIO 0 binding function
*
*Bind the struct to the device GPIO 1
*
* \return Return a pointer to a device struct type
* \bug No bugs detected
*/
void gpio1_bind();

#endif