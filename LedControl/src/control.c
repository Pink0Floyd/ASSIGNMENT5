
#include "control.h"

static float control_kp;
static float control_ki;

static float prop_error;
static float int_error;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

void control_init(float kp,float ki)
{
	control_kp=kp;
	control_ki=ki;

	printk("\tInitialised controller module\n");
}

float controller(float curr,float target)
{
	target=saturation(target,MIN_CONTROLLER_VALUE,MAX_CONTROLLER_VALUE);	// proporcional error
	curr=saturation(curr,MIN_CONTROLLER_VALUE,MAX_CONTROLLER_VALUE);		// proporcional error
	prop_error=target-curr;									// proporcional error

	int_error+=prop_error;									// integral error
	int_error=int_error*DECAY_FACTOR;							// integral error
	int_error=saturation(int_error,MIN_INT_ERROR,MAX_INT_ERROR);		// integral error

	float r=(control_kp*prop_error+control_ki*int_error);
	return saturation(r,MIN_CONTROLLER_VALUE,MAX_CONTROLLER_VALUE);
}