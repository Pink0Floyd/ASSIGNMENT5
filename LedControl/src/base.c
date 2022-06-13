
#include "base.h"

float saturation(float value,float min,float max)
{
	if(value<min){value=min;}
	else if(value>max){value=max;}
	return value;
}