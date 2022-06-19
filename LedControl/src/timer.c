
#include "timer.h"

time_data time_curr;
time_interval_data time_interval[N_INTERVAL];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

time_data format_time(time_data t)
{
	while(t.min>=HOUR_DURATION)
	{
		t.min-=HOUR_DURATION;
		t.hour++;
	}
	while(t.hour>=DAY_DURATION)
	{
		t.hour-=DAY_DURATION;
		t.day++;
	}
	while(t.day>=WEEK_DURATION)
	{
		t.day-=WEEK_DURATION;
	}
	return t;
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
	time_curr.min=0;
	time_curr.hour=0;
	time_curr.day=0;

	uint8_t k=0;
	while(k<N_INTERVAL)
	{
		time_interval[k].start=time_curr;
		time_interval[k].finish=time_curr;
		k++;
	}
	printk("Insert Initial Time:\n");
	set_time(scan_time());

	printk("\tInitialised timer module\n");
}

void update_time(uint8_t min)
{
	update_time_min(min);
}

void update_time_min(uint16_t min)
{
	time_curr.min+=min;
	time_curr=format_time(time_curr);
}

void update_time_hour(uint16_t hour)
{
	time_curr.hour+=hour;
	time_curr=format_time(time_curr);
}

void update_time_day(uint16_t day)
{
	time_curr.day+=day;
	time_curr=format_time(time_curr);
}

void set_time(time_data t)
{
	time_curr=t;
	time_curr=format_time(time_curr);
}

void set_interval(uint8_t n,time_data s,time_data f)
{
	n=saturation(n,0,N_INTERVAL-1);
	s=format_time(s);f=format_time(f);

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
	uint8_t r=N_INTERVAL;
	uint8_t k=0;
	while(k<N_INTERVAL)
	{
		if(compare_time(time_curr,time_interval[k].start)==-1)
		{
			if(compare_time(time_curr,time_interval[k].finish)==1)
			{
				r=k;
				break;
			}
		}
		k++;
	}
	return r;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

time_data read_time_curr()
{
	return time_curr;
}

void print_time(time_data t)
{
	printk("%u:%u:%u",t.day,t.hour,t.min);
}

time_data scan_time()
{
	time_data t;
	put_str("Day: ");t.day=(uint16_t)get_int();put_eol();
	put_str("Hour: ");t.hour=(uint16_t)get_int();put_eol();
	put_str("Min: ");t.min=(uint16_t)get_int();put_eol();
	t=format_time(t);
	return t;
}

void print_interval(uint8_t n)
{
	n=saturation(n,0,N_INTERVAL-1);
	print_time(time_interval[n].start);
	printk(" - ");
	print_time(time_interval[n].finish);
}