
#include "gpio.h"

const static struct device *gpio0_dev;						    // Pointer to GPIO device structure
static int gpio0_state=0;							    // The inicialization of the GPIO 0 struct is indicated by this variable

const static struct device *gpio1_dev;						    // Pointer to GPIO device structure
static int gpio1_state=0;							    // The initialization of the GPIO 1 struct is indicated by this variable    
	    
///////////////////////////////////////////////////////////////////////////////////////
//  Private Functions:
void gpio0_bind()
{
      gpio0_dev=device_get_binding(GPIO0_LABEL);				    // Bind the struct       

      if(PRINT_GPIB_DEBUG)
      {
		if(gpio0_dev==NULL)
		{
			printk("Failed to bind to GPIO0\n\r");        
			return;
		}
		else
		{
			printk("Bind to GPIO0 successfull \n\r");        
		} 
      }
	gpio0_state=1;								    // It means that gpio0_device it was already initialised						      
}

void gpio1_bind()
{
      gpio1_dev=device_get_binding(GPIO1_LABEL);				    // Bind the struct         

      if(PRINT_GPIB_DEBUG)
      {    
		if(gpio1_dev==NULL)
		{
			printk("Failed to bind to GPIO1\n\r");        
			return;
		}
		else
		{
			printk("Bind to GPIO1 successfull \n\r");        
		}  
      }	    
      gpio1_state=1;								    // It means that gpio0_device it was already initialised
}

///////////////////////////////////////////////////////////////////////////////////////
//  Public Functions:

struct device *gpio0_init()
{
	struct device* r;
      if(gpio0_state==0)
      {
	    gpio0_bind();
	    if(PRINT_GPIB_DEBUG)
	    {
		  printk("GPIO 0 initialised for the first time\n\r");
	    }
	    r=(struct device*)gpio0_dev;
      }
      else
      {
	    if(PRINT_GPIB_DEBUG)
	    {
		  printk("GPIO 1 already Initialised\n\r");
	    }
	    r=(struct device*)gpio0_dev;
      }
	return r;
}


/*
  const struct device *gpio1_dev;
  gpio1_dev=gpio1_init();
*/

struct device *gpio1_init()
{
	struct device* r;
      if(gpio1_state==0)
      {
	    gpio1_bind();
	    if(PRINT_GPIB_DEBUG)
	    {
		  printk("GPIO 1 initialised for the first time\n\r");
	    }
	    r=(struct device*)gpio1_dev;
      }
      else
      {
	     if(PRINT_GPIB_DEBUG)
	    {
		  printk("GPIO 1 already Initialised\n\r");
	    }
	    r=(struct device*)gpio1_dev;
      }
	return r;
}