/**
* \file schedule.h
* \brief Schedule module
*
* This module contains functions to implement a schedule
*
* \author Filipe Loureiro & Miguel Silva
* \date 18/06/22
* \version 5.2
* \bug No bugs found
*/

#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#include "base.h"
#include "timer.h"

#define MIN_LIGHT 0
#define MAX_LIGHT 100

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

uint8_t get_li();
time_data get_start();
time_data get_finish();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

void set_period();

#endif