#include "pwm.h"

// Global Variables:

static const struct device *pwm0_dev;				  // Pointer to PWM device structure 
static unsigned int pwmPeriod_us = 1000;			  // PWM priod in us

void pwm_init()
{
      // Initialize PWM:
      pwm0_dev = device_get_binding(DT_LABEL(PWM0_NID));
      if (pwm0_dev == NULL) 
      {
	    printk("\tError: Failed to bind to PWM0\n r");
	    return;
      }
      printk("\tInitialised PWM module\n");
}

void pwm_led_set(uint8_t dutycycle)
{
	dutycycle=saturation(dutycycle,PWM_DUTYCYCLE_MIN,PWM_DUTYCYCLE_MAX);
	dutycycle=PWM_DUTYCYCLE_MAX-dutycycle+PWM_DUTYCYCLE_MIN;
      int ret[4]={};
      ret[0] = pwm_pin_set_usec(pwm0_dev, OUTPUT_PIN, pwmPeriod_us,(unsigned int)(pwmPeriod_us*dutycycle/100), PWM_POLARITY_NORMAL);
      if (ret[0]+ret[1]+ret[2]+ret[3]!=0)
	{
		printk("\tError: failed to set pulse width\n");
		return;
      }
}