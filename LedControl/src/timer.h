/**
* \file timer.h
* \brief Timer module
*
* This module contains functions to implement timer functionalities
*
* \author Filipe Loureiro & Miguel Silva
* \date 19/06/22
* \version 5.14
* \bug No bugs found
*/

#ifndef _TIMER_H
#define _TIMER_H

#define HOUR_DURATION 60
#define DAY_DURATION 24
#define WEEK_DURATION 7

#define N_INTERVAL ((WEEK_DURATION+1)*2)

#include "base.h"
#include "uart.h"

typedef struct time_data
{
	uint16_t day;
	uint16_t hour;
	uint16_t min;
}time_data;

typedef struct time_interval_data
{
	time_data start;
	time_data finish;
}time_interval_data;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

//time_data format_time(time_data t);
//int8_t compare_time(time_data t1,time_data t2);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

void timer_init();
void update_time(uint8_t min);
void update_time_min(uint16_t min);
void update_time_hour(uint16_t hour);
void update_time_day(uint16_t day);
void set_time(time_data t);
void set_interval(uint8_t n,time_data s,time_data f);
uint8_t check_interval();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

time_data read_time_curr();
void print_time(time_data t);
time_data scan_time();
void print_interval(uint8_t n);

#endif