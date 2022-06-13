
#include "filter.h"

static filter_buffer buffer;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

float read_avg()
{
	float avg=buffer.samples_avg;		// return last calculated average
	return (avg-MIN_SAMPLE_VALUE)*(MAX_FILTER_VALUE-MIN_FILTER_VALUE)/(MAX_SAMPLE_VALUE-MIN_SAMPLE_VALUE);
}

void insert_sample(uint16_t sample)
{
	sample=saturation(sample,MIN_SAMPLE_VALUE,MAX_SAMPLE_VALUE);	// saturate sample
	buffer.count++;									// update count
	buffer.pointer=(buffer.pointer+1)%FILTER_BUFFER_SIZE;			// update pointer
	buffer.array[buffer.pointer]=sample;					// insert accepted sample
}

void avg_samples()
{
	if(buffer.count>0&&buffer.count<FILTER_BUFFER_SIZE)					// buffer not full
	{													//
		buffer.samples_avg=buffer.samples_avg*(buffer.count-1)/buffer.count;	// resize past samples contribution
		buffer.samples_avg+=buffer.array[buffer.pointer]/buffer.count;		// add new sample contribution
	}													//

	else if(buffer.count>=FILTER_BUFFER_SIZE)												// buffer full
	{																		//
		buffer.samples_avg-=buffer.array[(buffer.pointer+1)%FILTER_BUFFER_SIZE]/(FILTER_BUFFER_SIZE-1);		// remove oldest sample contribution
		buffer.samples_avg+=buffer.array[buffer.pointer]/(FILTER_BUFFER_SIZE-1);					// add new sample contribution
	}																		//
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

void filter_init()
{
	uint8_t k=0;
	while(k<FILTER_BUFFER_SIZE)
	{
		buffer.array[k]=0;
		k++;
	}
	buffer.pointer=FILTER_BUFFER_SIZE-1;
	buffer.count=0;
	buffer.samples_avg=0;
	printk("\tInitialised filter operation\n");
}

float filter(uint16_t in)
{
	insert_sample(in);
	avg_samples();
	return read_avg();
}
