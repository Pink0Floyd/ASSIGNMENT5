/**
* \file timer.h
* \brief Timer module
*
* This module contains functions to implement timer functionalities
*
* \author Filipe Loureiro & Miguel Silva
* \date 13/06/22
* \version 5.2
* \bug Remains untested
*/

#ifndef _TIMER_H
#define _TIMER_H

#define MIN_SEC 0
#define MAX_SEC 60
#define MIN_MIN 0
#define MAX_MIN 60
#define MIN_HOUR 0
#define MAX_HOUR 24
#define MIN_DAY 0
#define MAX_DAY 365

#include "base.h"

typedef struct time_data
{
	uint8_t day;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
}time_data;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

void timer_init();

#endif