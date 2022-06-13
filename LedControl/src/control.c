
#include "control.h"

static float prop_error;
static float int_error;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

float saturation(float value, float min,float max)
{
	if(value<min){value=min;}
	else if(value>max){value=max;}
	return value;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

float controller(float curr,float target)
{
	target=saturation(target,MIN_CONTROLLER_VALUE,MAX_CONTROLLER_VALUE);	// proporcional error
	curr=saturation(curr,MIN_CONTROLLER_VALUE,MAX_CONTROLLER_VALUE);		// proporcional error
	prop_error=target-curr;									// proporcional error

	int_error+=prop_error;									// integral error
	int_error=int_error*DECAY_FACTOR;							// integral error
	int_error=saturation(int_error,MIN_INT_ERROR,MAX_INT_ERROR);		// integral error

	float r=(KP*prop_error+KI*int_error);
	return saturation(r,MIN_CONTROLLER_VALUE,MAX_CONTROLLER_VALUE);
}