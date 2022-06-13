
#include "base.h"
#include "gpio.h"
#include "adc.h"
#include "filter.h"
#include "control.h"
#include "pwm.h"

#define PRINT_INIT 1		///< enable for thread initialisation prints
#define PRINT_LOOP 0		///< enable for thread loop prints

#define SAMPLING_PERIOD 1000		///< sampling period in miliseconds

#define SAMPLING_PRIO 1			///< sampling thread priority
#define FILTERING_PRIO 1		///< filtering thread priority
#define CONTROLLING_PRIO 1		///< controlling thread priority
#define ACTUATING_PRIO 1		///< actuating thread priority

#define SAMPLING_STACK_SIZE 512						///< sampling thread stack size
K_THREAD_STACK_DEFINE(sampling_stack,SAMPLING_STACK_SIZE);		///< sampling thread stack size
#define FILTERING_STACK_SIZE 512						///< filtering thread stack size
K_THREAD_STACK_DEFINE(filtering_stack,FILTERING_STACK_SIZE);	///< filtering thread stack size
#define CONTROLLING_STACK_SIZE 512						///< controlling thread stack size
K_THREAD_STACK_DEFINE(contrlling_stack,CONTROLLING_STACK_SIZE);	///< controlling thread stack size
#define ACTUATING_STACK_SIZE 512						///< actuating thread stack size
K_THREAD_STACK_DEFINE(actuating_stack,ACTUATING_STACK_SIZE);	///< actuating thread stack size

struct k_thread sampling_data;	///< sampling thread initialisation
k_tid_t sampling_tid;			///< sampling thread initialisation
struct k_thread filtering_data;	///< filtering thread initialisation
k_tid_t filtering_tid;			///< filtering thread initialisation
struct k_thread controlling_data;	///< controlling thread initialisation
k_tid_t controlling_tid;		///< controlling thread initialisation
struct k_thread actuating_data;	///< actuating thread initialisation
k_tid_t actuating_tid;			///< actuating thread initialisation

struct k_sem sem_samp;			///< sampling finished semafore
struct k_sem sem_filt;			///< filtering finished semafore
struct k_sem sem_contr;			///< controlling finished semafore

uint16_t filt_in;				///< shared memory between sampling and filtering
uint16_t contr_in;			///< shared memory between filtering and controlling
uint16_t act_in;				///< shared memory between controlling and actuating

float target=50;

void sampling(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("Launched sampling thread\n");

	int64_t curr_time=k_uptime_get();
	int64_t end_time=k_uptime_get()+SAMPLING_PERIOD;
	while(1)
	{
		filt_in=adc_sample();					// sample
		if(!PRINT_LOOP)
		printk("%u ",filt_in); 
		if(PRINT_LOOP)
		printk("sampling: sampled %u\n",filt_in);

		k_sem_give(&sem_samp);				// wake up filtering
		if(PRINT_LOOP)
		printk("sampling: finished sampling\n");

		curr_time=k_uptime_get();				// sleep until next sampling period
		if(curr_time<end_time)					// sleep until next sampling period
		{								// sleep until next sampling period
			k_msleep(end_time-curr_time);			// sleep until next sampling period
		}								// sleep until next sampling period
		end_time+=SAMPLING_PERIOD;				// sleep until next sampling period
	}
}

void filtering(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("Launched filtering thread\n");
	while(1)
	{
		if(PRINT_LOOP)
		printk("filtering: waiting for sampling to finish\n");
		k_sem_take(&sem_samp,K_FOREVER);							// sleep until sampling finishes
		if(PRINT_LOOP)
		printk("filtering: sampling finished\n");

		contr_in=filter(filt_in);								// filter
		if(!PRINT_LOOP)
		printk("-> %u ",contr_in);
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
	printk("Launched controlling thread\n");

	while(1)
	{
		if(PRINT_LOOP)
		printk("controlling: waiting for a sample from sampling\n");
		k_sem_take(&sem_filt,K_FOREVER);							// sleep until filtering finishes
		if(PRINT_LOOP)
		printk("controlling: filtering finished\n");

		act_in=controller(contr_in,target);							// control
		if(!PRINT_LOOP)
		printk("-> %u ",act_in);
		if(PRINT_LOOP)
		printk("controlling: contrlled %u to %u\n",contr_in,act_in);

		k_sem_give(&sem_contr);									// wake up actuating
		if(PRINT_LOOP)
		printk("controlling: finished controlling\n");
	}
}

void actuating(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("Launched actuating thread\n");

	while(1)
	{
		if(PRINT_LOOP)
		printk("actuating: waiting for a filtered sample from filtering\n");
		k_sem_take(&sem_contr,K_FOREVER);							// sleep until controlling finishes
		if(PRINT_LOOP)
		printk("actuating: got a filtered sample from filtering\n");

		pwm_led_set(act_in);									// act
		if(PRINT_LOOP)
		printk("actuating: led has been set to %u %%\n",act_in);
	}
}

void main()
{
	printk("\n\n\nLed Controller \n");

	adc_init();
	filter_init();
	pwm_init();

	k_sem_init(&sem_samp,0,1);
	k_sem_init(&sem_filt,0,1);
	k_sem_init(&sem_contr,0,1);

	sampling_tid=k_thread_create(&sampling_data,sampling_stack,K_THREAD_STACK_SIZEOF(sampling_stack),			// create sampling thread
		sampling,NULL,NULL,NULL,SAMPLING_PRIO,0,K_NO_WAIT);										// create sampling thread

	filtering_tid=k_thread_create(&filtering_data,filtering_stack,K_THREAD_STACK_SIZEOF(filtering_stack),			// create filtering thread
		filtering,NULL,NULL,NULL,FILTERING_PRIO,0,K_NO_WAIT);										// create filtering thread

	controlling_tid=k_thread_create(&controlling_data,controlling_stack,K_THREAD_STACK_SIZEOF(controlling_stack),	// create actuating thread
		controlling,NULL,NULL,NULL,CONTROLLING_PRIO,0,K_NO_WAIT);									// create actuating thread

	actuating_tid=k_thread_create(&actuating_data,actuating_stack,K_THREAD_STACK_SIZEOF(actuating_stack),			// create actuating thread
		actuating,NULL,NULL,NULL,ACTUATING_PRIO,0,K_NO_WAIT);										// create actuating thread
}