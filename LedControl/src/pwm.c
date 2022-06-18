#include "pwm.h"

// Global Variables:

static const struct device *pwm0_dev;			    // pointer to PWM device structure 
static uint32_t period;					    // PWM period in microseconds

void pwm_init(uint32_t p)
{
      pwm0_dev = device_get_binding(DT_LABEL(PWM0_NID));
      if(pwm0_dev==NULL) 
      {
		printk("\tError: Failed to bind to PWM0\n r");
      }
	else
	{
		printk("\tInitialised PWM module\n");
	}

	period=p;					// set PWM period
	pwm_led_set(50);				// init PWM with 50% dutycycle
}

void pwm_led_set(uint8_t dutycycle)
{
	dutycycle=saturation(dutycycle,PWM_DUTYCYCLE_MIN,PWM_DUTYCYCLE_MAX);		// saturate dutycycle value
	dutycycle=PWM_DUTYCYCLE_MAX-dutycycle+PWM_DUTYCYCLE_MIN;				// invert PWM polarity

      int ret=pwm_pin_set_usec(pwm0_dev,OUTPUT_PIN,period,(uint32_t)(period*dutycycle/100),PWM_POLARITY_NORMAL);
      if(ret!=0)
	{
		printk("\tError: failed to set pulse width\n");
      }
}