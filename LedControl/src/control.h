/**
* \file control.h
* \brief Controller module
*
* This module contains functions to implement the controller
*
* \author Filipe Loureiro & Miguel Silva
* \date 18/06/22
* \version 5.8
* \bug No bugs found
*/

#ifndef _CONTROL_H
#define _CONTROL_H

#include "base.h"

#define DECAY_FACTOR 0.99
#define MIN_INT_ERROR -12
#define MAX_INT_ERROR 12

#define MIN_CONTROLLER_VALUE 4
#define MAX_CONTROLLER_VALUE 96

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

void control_init(float kp,float ki);
float controller(float curr,float target);

#endif