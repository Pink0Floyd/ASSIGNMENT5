/**
* \file control.h
* \brief Controller module
*
* This module contains functions to implement the controller
*
* \author Filipe Loureiro & Miguel Silva
* \date 13/06/22
* \version 5.7
* \bug No bugs found
*/

#ifndef _CONTROL_H
#define _CONTROL_H

#include "base.h"

#define DECAY_FACTOR 0.99
#define MIN_INT_ERROR -12
#define MAX_INT_ERROR 12

#define MIN_CONTROLLER_VALUE 0
#define MAX_CONTROLLER_VALUE 100

#define KP 6
#define KI 2

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

//float saturation(float value,float min,float max);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

float controller(float curr,float target);

#endif