
#include "schedule.h"

uint8_t light_intensity[N_INTERVAL];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

uint8_t get_li()
{
	put_str("Period ID:");uint8_t n=(uint8_t)get_int();
	put_str("Light Intensity:");uint8_t li=(uint8_t)get_int();
	n=saturation(n,0,N_INTERVAL-1);
	li=saturation(li,MIN_LIGHT,MAX_LIGHT);
	light_intensity[n]=li;
	return n;
}

time_data get_start()
{
	put_str("Start time:\n");
	return scan_time();
}

time_data get_finish()
{
	put_str("Finish time:\n");
	return scan_time();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

void set_period()
{
	uint8_t n=get_li();
	time_data s=get_start();
	time_data f=get_finish();
	set_interval(n,s,f);
}