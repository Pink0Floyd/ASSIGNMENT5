/**
* \file control.h
* \brief Controller module
*
* This module contains functions to implement the controller
*
* \author Filipe Loureiro & Miguel Silva
* \date 20/06/22
* \version 5.10
* \bug No bugs found
*/

#ifndef _CONTROL_H
#define _CONTROL_H

#include "base.h"
#include "math.h"

#define DECAY_FACTOR 0.99
#define MIN_INT_ERROR -1200
#define MAX_INT_ERROR 1200

#define MIN_CONTROLLER_VALUE 0
#define MAX_CONTROLLER_VALUE 100

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

void control_init(float kp,float ki);
float controller(float curr,float target);

#endif