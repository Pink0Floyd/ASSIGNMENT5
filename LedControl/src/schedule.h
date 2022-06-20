/**
* \file schedule.h
* \brief Schedule module
*
* This module contains functions to implement a schedule
*
* \author Filipe Loureiro & Miguel Silva
* \date 20/06/22
* \version 5.8
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

void schedule_init();
void set_period();
uint8_t check_light(uint8_t light_curr);
void print_schedule();

#endif