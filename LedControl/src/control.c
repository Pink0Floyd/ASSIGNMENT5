
#include "control.h"

static float prop_error;
static float int_error;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

float saturation(float value, float min,float max)
{
	if(value<min)
	{
		value=min;
	}
	else if(value>max)
	{
		value=max;
	}
	return value;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float controller(float curr,float target)
{
	target=saturation(target,MIN_CONTROLLER_VALUE,MAX_CONTROLLER_VALUE);
	curr=saturation(curr,MIN_CONTROLLER_VALUE,MAX_CONTROLLER_VALUE);
	prop_error=target-curr;
	int_error+=prop_error;
	int_error=int_error*DECAY_FACTOR;
	int_error=saturation(int_error,MIN_INT_ERROR,MAX_INT_ERROR);
	float kp=KP*prop_error;
	float ki=KI*int_error;
	return (kp+ki);
}