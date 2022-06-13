
#include "timer.h"

time_data time;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

void timer_init()
{
	time.sec=0;
	time.min=0;
	time.hour=0;
	time.day=0;
	printk("\tInitialised timer operation\n");
}

void update_time(uint8_t sec)
{
	update_time_sec(sec);
}

void update_time_sec(uint8_t sec)
{
	
}

void update_time_min(uint8_t min)
{
	
}

void update_time_hour(uint8_t hour)
{
	
}

void update_time_day(uint8_t day)
{
	
}

void set_time(uint8_t day,uint8_t hour,uint8_t min,uint8_t sec)
{
	
}