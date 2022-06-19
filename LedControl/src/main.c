
#include "base.h"
#include "gpio.h"
#include "adc.h"
#include "filter.h"
#include "control.h"
#include "pwm.h"
#include "buttons.h"
#include "uart.h"
#include "timer.h"
#include "schedule.h"

#define PRINT_INIT 1			///< enable for thread initialisation prints
#define PRINT_LOOP 1			///< enable for thread loop prints

#define PWM_PERIOD 1			///<< period for the PWM signal in microseconds

#define SAMPLING_PERIOD 100000		///< sampling period in miliseconds
#define BUTTOING_PERIOD 100000		///< buttons check period in miliseconds
#define TIMING_PERIOD 6000			///< timing period in miliseconds

#define INITIAL_STATE 2				///< state machine initial state

#define KP 6.0				///< controller proportional coeficient
#define KI 2.0				///< controller intergral coeficient

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SAMPLING_PRIO 3			///< sampling thread priority
#define FILTERING_PRIO 1		///< filtering thread priority
#define CONTROLLING_PRIO 1		///< controlling thread priority
#define ACTUATING_PRIO 1		///< actuating thread priority
#define BUTTONING_PRIO 2		///< buttoing thread priority
#define MACHINING_PRIO 2		///< machining thread priority
#define UARTING_PRIO 2			///< uarting thread priority
#define TIMING_PRIO 4			///< timing thread priority
#define SCHEDULING_PRIO 1		///< scheduling thread priority

#define STACK_SIZE 2048							///< thread stack size
K_THREAD_STACK_DEFINE(sampling_stack,STACK_SIZE);		///< sampling thread stack size
K_THREAD_STACK_DEFINE(filtering_stack,STACK_SIZE);		///< filtering thread stack size
K_THREAD_STACK_DEFINE(controlling_stack,STACK_SIZE);		///< controlling thread stack size
K_THREAD_STACK_DEFINE(actuating_stack,STACK_SIZE);		///< actuating thread stack size
K_THREAD_STACK_DEFINE(buttoing_stack,STACK_SIZE);		///< buttoing thread stack size
K_THREAD_STACK_DEFINE(machining_stack,STACK_SIZE);		///< machining thread stack size
K_THREAD_STACK_DEFINE(uarting_stack,STACK_SIZE);		///< uarting thread stack size
K_THREAD_STACK_DEFINE(timing_stack,STACK_SIZE);			///< timing thread stack size
K_THREAD_STACK_DEFINE(scheduling_stack,STACK_SIZE);		///< timing thread stack size

struct k_thread sampling_data;	///< sampling thread initialisation
k_tid_t sampling_tid;			///< sampling thread initialisation
struct k_thread filtering_data;	///< filtering thread initialisation
k_tid_t filtering_tid;			///< filtering thread initialisation
struct k_thread controlling_data;	///< controlling thread initialisation
k_tid_t controlling_tid;		///< controlling thread initialisation
struct k_thread actuating_data;	///< actuating thread initialisation
k_tid_t actuating_tid;			///< actuating thread initialisation
struct k_thread buttoing_data;	///< buttoing thread initialisation
k_tid_t buttoing_tid;			///< buttoing thread initialisation
struct k_thread machining_data;	///< machining thread initialisation
k_tid_t machining_tid;			///< machining thread initialisation
struct k_thread uarting_data;		///< uarting thread initialisation
k_tid_t uarting_tid;			///< uarting thread initialisation
struct k_thread timing_data;		///< timing thread initialisation
k_tid_t timing_tid;			///< timing thread initialisation
struct k_thread scheduling_data;	///< scheduling thread initialisation
k_tid_t scheduling_tid;			///< scheduling thread initialisation

struct k_sem sem_samp;			///< sampling finished semafore
struct k_sem sem_filt;			///< filtering finished semafore
struct k_sem sem_contr;			///< controlling finished semafore
struct k_sem sem_but;			///< buttoing finished semafore
struct k_sem sem_mach;			///< machining finished semafore
struct k_sem sem_tim;			///< timing finished semafore

uint16_t filt_in=0;			///< shared memory between sampling and filtering
uint16_t contr_in=0;			///< shared memory between filtering and controlling
uint16_t act_in=0;			///< shared memory between controlling and actuating
uint8_t button_flag=0;			///< shared memory between buttoing and machining
uint8_t state=INITIAL_STATE;		///< shared memory between machining and uarting
uint8_t target=50;			///< shared memory between scheduling and controlling

void sampling(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("\tLaunched sampling thread\n");

	int64_t curr_time=k_uptime_get();
	int64_t end_time=k_uptime_get()+SAMPLING_PERIOD;
	while(1)
	{
		filt_in=adc_sample();					// sample
		if(PRINT_LOOP)
		printk("\nsampling: sampled %u\n",filt_in);

		k_sem_give(&sem_samp);				// wake up filtering
		if(PRINT_LOOP)
		printk("sampling: finished sampling\n");

		curr_time=k_uptime_get();				// sleep until next period
		if(curr_time<end_time)					// sleep until next period
		{								// sleep until next period
			k_msleep(end_time-curr_time);			// sleep until next period
		}								// sleep until next period
		end_time+=SAMPLING_PERIOD;				// sleep until next period
	}
}

void filtering(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("\tLaunched filtering thread\n");
	while(1)
	{
		if(PRINT_LOOP)
		printk("filtering: waiting for sampling to finish\n");
		k_sem_take(&sem_samp,K_FOREVER);							// sleep until sampling finishes
		if(PRINT_LOOP)
		printk("filtering: sampling finished\n");

		contr_in=filter(filt_in);								// filter
		if(PRINT_LOOP)
		printk("filtering: filtered %u to %u\n",filt_in,contr_in);

		k_sem_give(&sem_filt);									// wake up controlling
		if(PRINT_LOOP)
		printk("filtering: finished filtering\n");
	}
}

void controlling(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("\tLaunched controlling thread\n");

	while(1)
	{
		if(PRINT_LOOP)
		printk("controlling: waiting for filtering to finish\n");
		k_sem_take(&sem_filt,K_FOREVER);							// sleep until filtering finishes
		if(PRINT_LOOP)
		printk("controlling: filtering finished\n");

		act_in=controller(contr_in,target);							// control
		if(PRINT_LOOP)
		printk("controlling: controlled %u to %u\n",contr_in,act_in);

		k_sem_give(&sem_contr);									// wake up actuating
		if(PRINT_LOOP)
		printk("controlling: finished controlling\n");
	}
}

void actuating(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("\tLaunched actuating thread\n");

	while(1)
	{
		if(PRINT_LOOP)
		printk("actuating: waiting for controlling to finish\n");
		k_sem_take(&sem_contr,K_FOREVER);							// sleep until controlling finishes
		if(PRINT_LOOP)
		printk("actuating: got a filtered sample from filtering\n");

		pwm_led_set(act_in);									// act
		if(PRINT_LOOP)
		printk("actuating: pwm has been set to %u %%\n",act_in);
	}
}

void buttoing(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("\tLaunched buttoing thread\n");

	int64_t curr_time=k_uptime_get();
	int64_t end_time=k_uptime_get()+BUTTOING_PERIOD;
	while(1)
	{
		button_flag=read_buttons(4)*8+read_buttons(3)*4+read_buttons(2)*2+read_buttons(1)*1;		// read buttons
		if(PRINT_LOOP)
		printk("buttoing: %u read from buttons\n",button_flag);

		k_sem_give(&sem_but);
		if(PRINT_LOOP)
		printk("buttoing: finished buttoing\n");

		curr_time=k_uptime_get();				// sleep until next period
		if(curr_time<end_time)					// sleep until next period
		{								// sleep until next period
			k_msleep(end_time-curr_time);			// sleep until next period
		}								// sleep until next period
		end_time+=BUTTOING_PERIOD;				// sleep until next period
	}
}

void machining()
{	
	while(state==1||state==2)
	{
		if(PRINT_LOOP)
		printk("machining: waiting for buttoing to finish\n");
		k_sem_take(&sem_but,K_FOREVER);
		if(PRINT_LOOP)
		printk("machining: buttoing has finished\n");

		if(PRINT_LOOP)
		printk("machining: entering state %u\n",state);
		switch(state)
		{
			case 1:							// start of state 1 (manual state)
				if(button_flag==2)				// next state condition
				{							// next state condition
					state=2;					// next state condition
				}							// next state condition
				break;						// end of state 1 (manual state)

			case 2:							// start of state 2 (automatic state)
				if(button_flag==1)				// next state condition
				{							// next state condition
					state=1;					// next state condition
				}							// next state condition
				break;						// end of state 2 (automatic state)
		}
		if(PRINT_LOOP)
		printk("machining: exiting to state %u",state);

		k_sem_give(&sem_mach);
		if(PRINT_LOOP)
		printk("machining: finished machining\n");
	}
	printk("machining: unknown state\n");
}

void uarting(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("\tLaunched uarting thread\n");


	int i=0;
	while(1)
	{
		if(PRINT_LOOP)
		printk("uarting: waiting for machining to finish\n");
		k_sem_take(&sem_mach,K_FOREVER);
		if(PRINT_LOOP)
		printk("uarting: machining has finished\n");

		if(state==2)
		{
			i=get_int();
			if(PRINT_LOOP)
			printk("uarting: Received int %i\n",i);
		}
	}
}

void timing(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("\tLaunched timing thread\n");

	int64_t curr_time=k_uptime_get();
	int64_t end_time=k_uptime_get()+TIMING_PERIOD;
	while(1)
	{
		update_time(1);						// advance a minute
		if(PRINT_LOOP)
		printk("timing: a minute has passed\n");
		if(PRINT_LOOP)
		print_time(read_time_curr());
		k_sem_give(&sem_tim);
		if(PRINT_LOOP)
		printk("timing: finished timing\n");

		curr_time=k_uptime_get();				// sleep until next period
		if(curr_time<end_time)					// sleep until next period
		{								// sleep until next period
			k_msleep(end_time-curr_time);			// sleep until next period
		}								// sleep until next period
		end_time+=TIMING_PERIOD;				// sleep until next period
	}
}

void scheduling(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("\tLaunched scheduling thread\n");

	while(1)
	{
		if(PRINT_LOOP)
		printk("scheduling: waiting for timing to finish\n");
		k_sem_take(&sem_tim,K_FOREVER);
		if(PRINT_LOOP)
		printk("scheduling: timing has finished\n");

		target=check_light();
		if(PRINT_LOOP)
		printk("scheduling: this period's light is %u\n",target);
	}
}

void main()
{
	printk("\n\n\nLed Controller \n");

	adc_init();
	filter_init();
	control_init(KI,KP);
	pwm_init(PWM_PERIOD);
	buttons_init_(15,'h');
	uart_init();
	timer_init();
	schedule_init();
	printk("\n\n\n");

	k_sem_init(&sem_samp,0,1);		// init sampling finished semafore
	k_sem_init(&sem_filt,0,1);		// init filtering finished semafore
	k_sem_init(&sem_contr,0,1);		// init controlling finished semafore
	k_sem_init(&sem_but,0,1);		// init buttoing finished semafore
	k_sem_init(&sem_mach,0,1);		// init machining finished semafore
	k_sem_init(&sem_tim,0,1);		// init timing finished semafore

	sampling_tid=k_thread_create(&sampling_data,sampling_stack,K_THREAD_STACK_SIZEOF(sampling_stack),			// create sampling thread
		sampling,NULL,NULL,NULL,SAMPLING_PRIO,0,K_NO_WAIT);										// create sampling thread

	filtering_tid=k_thread_create(&filtering_data,filtering_stack,K_THREAD_STACK_SIZEOF(filtering_stack),			// create filtering thread
		filtering,NULL,NULL,NULL,FILTERING_PRIO,0,K_NO_WAIT);										// create filtering thread

	controlling_tid=k_thread_create(&controlling_data,controlling_stack,K_THREAD_STACK_SIZEOF(controlling_stack),	// create actuating thread
		controlling,NULL,NULL,NULL,CONTROLLING_PRIO,0,K_NO_WAIT);									// create actuating thread

	actuating_tid=k_thread_create(&actuating_data,actuating_stack,K_THREAD_STACK_SIZEOF(actuating_stack),			// create actuating thread
		actuating,NULL,NULL,NULL,ACTUATING_PRIO,0,K_NO_WAIT);										// create actuating thread

	buttoing_tid=k_thread_create(&buttoing_data,buttoing_stack,K_THREAD_STACK_SIZEOF(buttoing_stack),			// create buttoing thread
		buttoing,NULL,NULL,NULL,BUTTONING_PRIO,0,K_NO_WAIT);										// create buttoing thread

	machining_tid=k_thread_create(&machining_data,machining_stack,K_THREAD_STACK_SIZEOF(machining_stack),			// create machining thread
		machining,NULL,NULL,NULL,MACHINING_PRIO,0,K_NO_WAIT);										// create machining thread
	
	uarting_tid=k_thread_create(&uarting_data,uarting_stack,K_THREAD_STACK_SIZEOF(uarting_stack),				// create uarting thread
		uarting,NULL,NULL,NULL,UARTING_PRIO,0,K_NO_WAIT);										// create uarting thread
	
	timing_tid=k_thread_create(&timing_data,timing_stack,K_THREAD_STACK_SIZEOF(timing_stack),					// create timing thread
		timing,NULL,NULL,NULL,TIMING_PRIO,0,K_NO_WAIT);											// create timing thread
	
	scheduling_tid=k_thread_create(&scheduling_data,scheduling_stack,K_THREAD_STACK_SIZEOF(scheduling_stack),		// create scheduling thread
		scheduling,NULL,NULL,NULL,SCHEDULING_PRIO,0,K_NO_WAIT);									// create scheduling thread
}