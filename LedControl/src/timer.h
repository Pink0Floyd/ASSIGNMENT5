/**
* \file timer.h
* \brief Timer module
*
* This module contains functions to implement timer functionalities
*
* \author Filipe Loureiro & Miguel Silva
* \date 15/06/22
* \version 5.6
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
#define MAX_DAY 7

#include "base.h"

typedef struct time_data
{
	uint16_t day;
	uint16_t hour;
	uint16_t min;
}time_data;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

//void format_time()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

void timer_init();
void update_time(uint8_t min);
void update_time_min(uint16_t min);
void update_time_hour(uint16_t hour);
void update_time_day(uint16_t day);
void set_time(uint16_t day,uint16_t hour,uint16_t min);

#endif