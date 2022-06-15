
#include "timer.h"

time_data time;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

void format_time()
{
	while(time.min>=60)
	{
		time.min-=60;
		time.hour++;
	}
	while(time.hour>=24)
	{
		time.hour-=24;
		time.day++;
	}
	while(time.day>=7)
	{
		time.day-=7;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

void timer_init()
{
	time.min=0;
	time.hour=0;
	time.day=0;
	printk("\tInitialised timer operation\n");
}

void update_time(uint8_t min)
{
	update_time_min(min);
}

void update_time_min(uint16_t min)
{
	time.min+=min;
	format_time();
}

void update_time_hour(uint16_t hour)
{
	time.hour+=hour;
	format_time();
}

void update_time_day(uint16_t day)
{
	time.day+=day;
	format_time();
}

void set_time(uint16_t day,uint16_t hour,uint16_t min)
{
	time.day=day;
	time.hour=hour;
	time.min=min;
	format_time();
}