
#include "schedule.h"

uint8_t light_intensity[N_INTERVAL];
uint8_t default_light;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

uint8_t get_li()
{
	put_str("Period ID:");uint8_t n=(uint8_t)get_int();put_eol();
	put_str("Light Intensity:");uint8_t li=(uint8_t)get_int();put_eol();
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

void schedule_init()
{
	uint8_t k=0;
	while(k<N_INTERVAL)
	{
		light_intensity[k]=0;
		k++;
	}
	printk("\tInitialised schedule module\n");
}

void set_period()
{
	put_str("Setting a light period:");put_eol();
	uint8_t n=get_li();
	time_data s=get_start();
	time_data f=get_finish();
	set_interval(n,s,f);
}

int8_t check_light()
{
	uint8_t r=check_interval();
	if(r!=N_INTERVAL)
	{
		r=light_intensity[r];
		
	}
	else
	{
		r=MIN_LIGHT;
	}
	return (int8_t)r;
}

void print_schedule()
{
	printk("Schedule:\n\n");
	uint8_t k=0;
	while(k<N_INTERVAL)
	{
		printk(" %u light during\t",light_intensity[k]);
		print_interval(k);
		printk("\n");
		k++;
	}
}