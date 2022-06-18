
#include "timer.h"

time_data time;

time_interval_data time_interval[N_INTERVAL];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

void format_time()
{
	while(time.min>=HOUR_DURATION)
	{
		time.min-=HOUR_DURATION;
		time.hour++;
	}
	while(time.hour>=DAY_DURATION)
	{
		time.hour-=DAY_DURATION;
		time.day++;
	}
	while(time.day>=WEEK_DURATION)
	{
		time.day-=WEEK_DURATION;
	}
}

int8_t compare_time(time_data t1,time_data t2)
{
	int8_t r=0;
	if(t1.day<t2.day){r=1;}
	else if(t1.day>t2.day){r=-1;}
	else
	{
		if(t1.hour<t2.hour){r=1;}
		else if(t1.hour>t2.hour){r=-1;}
		else
		{
			if(t1.min<t2.min){r=1;}
			else if(t1.min>t2.min){r=-1;}
			else{r=0;}
		}
	}
	return r;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

void timer_init()
{
	time.min=0;
	time.hour=0;
	time.day=0;

	uint8_t k=0;
	while(k<N_INTERVAL)
	{
		time_interval[k].start=time;
		time_interval[k].finish=time;
		k++;
	}

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

void set_time(time_data t)
{
	time=t;
	format_time();
}

void set_interval(uint8_t n,time_data s,time_data f)
{
	int16_t i=compare_time(s,f);
	if(i==1)
	{
		time_interval[n].start=s;
		time_interval[n].finish=f;
	}
	else
	{
		time_interval[n].start=f;
		time_interval[n].finish=s;
	}
}

uint8_t check_interval()
{
	uint8_t k=0;
	while(k<N_INTERVAL)
	{
		if(compare_time(time,time_interval[k].start)==-1)
		{
			if(compare_time(time,time_interval[k].finish)==1)
			{
				break;
			}
		}
		k++;
	}
	return k;
}