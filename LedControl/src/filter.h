/**
* \file filter.h
* \brief Smart Filter module
*
* This module contains functions to implement the smart filter required
*
* \author Filipe Loureiro & Miguel Silva
* \date 13/06/22
* \version 5.5
* \bug Remains Untested
*/

#ifndef _FILTER_H
#define _FILTER_H

#include "base.h"

#define MIN_SAMPLE_VALUE 0			///< minimum sample value
#define MAX_SAMPLE_VALUE 1023			///< maximum sample value

#define FILTER_BUFFER_SIZE 13			///< number of samples in each average plus the excluded old sample
#define MIN_FILTER_VALUE 0			///< minimum filter value
#define MAX_FILTER_VALUE 100			///< maximum filter value

typedef struct filter_buffer
{
	float array[FILTER_BUFFER_SIZE];
	uint8_t pointer;
	uint8_t count;
	float samples_avg;
}filter_buffer;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

//float read_avg();
//void insert_sample(uint16_t sample);
//void avg_samples();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

/**
* \brief Filter initialisation function
*
* Initialises the filter buffer necessary for its operation
*
* \bug No bugs detected
*/
void filter_init();

/**
* \brief Filter operation function
*
* Inserts a new sample in the filter buffer, calculates the average of the samples in the filter buffer except the oldest and returns the last average calculated
*
* \param [IN] sample to be inserted
* \return last average calculated
* \bug No bugs detected
*/
float filter(uint16_t in);

#endif